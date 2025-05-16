import matplotlib.pyplot as plt
import seaborn as sns
import re
from matplotlib.cm import get_cmap

# Paste your clustering output here
raw_output = ""
with open("output.txt", "r") as file:
    raw_output = file.read()

def extract_points(block):
    return [
        tuple(map(float, line.strip().split()))
        for line in block.strip().split("\n")
        if re.match(r"^\s*-?\d*\.\d+\s+-?\d*\.\d+", line.strip())
    ]

def extract_clusters(section_name, text):
    section = re.search(rf"{section_name}.*?Clusters:(.*?)(?:Outliers:|Evaluation:|$)", text, re.DOTALL)
    if not section:
        return {}, []

    cluster_text = section.group(1)
    clusters = {}
    outliers = []

    cluster_matches = re.finditer(r"Cluster\s+(\d+):.*?Data points:(.*?)(?=Cluster\s+\d+:|$)", cluster_text, re.DOTALL)
    for match in cluster_matches:
        cluster_id = int(match.group(1))
        points = extract_points(match.group(2))
        clusters[cluster_id] = points

    outlier_match = re.search(rf"{section_name}.*?Outliers:(.*?)(?:Evaluation:|$)", text, re.DOTALL)
    if outlier_match:
        outlier_block = outlier_match.group(1).strip()
        lines = outlier_block.splitlines()
        if lines and re.match(r"^\s*-?\d*\.\d+\s+-?\d*\.\d+", lines[0].strip()):
            outliers = extract_points(outlier_block)

    return clusters, outliers

def plot_clusters(title, all_points, clusters, outliers):
    plt.figure(figsize=(8, 6))
    sns.set(style="whitegrid")
    cmap = get_cmap("tab10")

    for i, (cluster_id, points) in enumerate(clusters.items()):
        color = cmap(i % 10)
        plt.scatter(*zip(*points), color=color, label=f'Cluster {cluster_id}')
    
    if outliers:
        plt.scatter(*zip(*outliers), color='red', marker='x', s=100, label='Outliers')
    
    plt.scatter(*zip(*all_points), facecolors='none', edgecolors='gray', alpha=0.3, label='All points')

    plt.title(title)
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.legend()
    plt.tight_layout()
    plt.show()

# Extract data points
data_section = re.search(r"Data points:(.*?)Kmeans plus plus Clusters:", raw_output, re.DOTALL)
all_points = extract_points(data_section.group(1)) if data_section else []

# Extract clusters
kmeans_clusters, kmeans_outliers = extract_clusters("Kmeans plus plus", raw_output)
dbscan_clusters, dbscan_outliers = extract_clusters("dbscan", raw_output)
print("KMeans++ Clusters:", kmeans_clusters)
print("KMeans++ Outliers:", kmeans_outliers)

# Plot each clustering result in a separate figure
plot_clusters("KMeans++ Clustering", all_points, kmeans_clusters, kmeans_outliers)
plot_clusters("DBSCAN Clustering", all_points, dbscan_clusters, dbscan_outliers)
