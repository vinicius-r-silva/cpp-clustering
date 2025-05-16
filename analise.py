import matplotlib.pyplot as plt
import seaborn as sns
import re
from matplotlib.colors import hsv_to_rgb
import numpy as np

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
    section = re.search(rf"{section_name}.*?Clusters:(.*?)(?:Naive Kmeans|Kmeans plus plus|dbscan|Evaluation:|$)", text, re.DOTALL | re.IGNORECASE)
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

    outlier_match = re.search(rf"{section_name}.*?Outliers:(.*?)(?:Naive Kmeans|Kmeans plus plus|dbscan|Evaluation:|$)", text, re.DOTALL | re.IGNORECASE)
    if outlier_match:
        outlier_block = outlier_match.group(1).strip()
        lines = outlier_block.splitlines()
        if lines and re.match(r"^\s*-?\d*\.\d+\s+-?\d*\.\d+", lines[0].strip()):
            outliers = extract_points(outlier_block)

    return clusters, outliers

def generate_distinct_colors(n):
    hues = np.linspace(0, 1, n, endpoint=False)
    return [hsv_to_rgb((h, 0.75, 0.9)) for h in hues]

def plot_clusters(title, filename, all_points, clusters, outliers):
    plt.figure(figsize=(8, 6))
    sns.set(style="whitegrid")

    colors = generate_distinct_colors(len(clusters))

    for i, points in enumerate(clusters.values()):
        color = colors[i]
        plt.scatter(*zip(*points), color=color)

    if outliers:
        plt.scatter(*zip(*outliers), color='red', marker='x', s=100)

    plt.scatter(*zip(*all_points), facecolors='none', alpha=0.3)

    plt.title(title)
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.tight_layout()
    plt.savefig(filename, dpi=300)
    plt.close()
    print(f"Saved: {filename}")

data_section = re.search(r"Data points:(.*?)(Naive KMeans|Kmeans plus plus|dbscan)", raw_output, re.DOTALL | re.IGNORECASE)
all_points = extract_points(data_section.group(1)) if data_section else []

clustering_algos = [
    ("Naive KMeans", "naive_kmeans.png"),
    ("Kmeans plus plus", "kmeans_plus_plus.png"),
    ("dbscan", "dbscan.png")
]

for algo_name, filename in clustering_algos:
    clusters, outliers = extract_clusters(algo_name, raw_output)
    plot_clusters(algo_name, filename, all_points, clusters, outliers)