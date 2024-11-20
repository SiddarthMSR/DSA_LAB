import matplotlib.pyplot as plt
import ast

# Function to read the data from the file
def read_data(filename):
    with open(filename, "r") as file:
        data = file.read()
    # Convert the JSON-like string into a dictionary
    return ast.literal_eval(data)

# Visualization function
def visualize_knapsack(data):
    sticks = data["sticks"]
    target = data["target"]
    subset = data["subset"]
    remaining = target - sum(subset)

    # Input Visualization
    plt.figure(figsize=(12, 4))
    plt.title("Input Visualization: Sticks")
    for i, stick in enumerate(sticks):
        plt.barh(0, stick, left=sum(sticks[:i]), color=f"C{i}", edgecolor="black", label=f"Stick {i+1}: {stick}")
    plt.xlabel("Length")
    plt.yticks([])
    plt.legend(loc="upper center", bbox_to_anchor=(0.5, -0.2), ncol=4)
    plt.tight_layout()
    plt.savefig("input_visualization.png")
    plt.show()

    # Output Visualization
    plt.figure(figsize=(12, 4))
    plt.title("Output Visualization: Selected Sticks")
    for i, stick in enumerate(subset):
        plt.barh(0, stick, left=sum(subset[:i]), color=f"C{sticks.index(stick)}", edgecolor="black", label=f"Stick {sticks.index(stick)+1}: {stick}")
    plt.barh(0, remaining, left=sum(subset), color="gray", edgecolor="black", label=f"Remaining: {remaining}")
    plt.xlabel("Length")
    plt.yticks([])
    plt.legend(loc="upper center", bbox_to_anchor=(0.5, -0.2), ncol=4)
    plt.tight_layout()
    plt.savefig("output_visualization.png")
    plt.show()

# Main function to read and visualize
if __name__ == "__main__":
    data = read_data("output_data.txt")
    visualize_knapsack(data)
