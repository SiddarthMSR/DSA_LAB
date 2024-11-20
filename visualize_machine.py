import pandas as pd
import matplotlib.pyplot as plt

# Load the results
df = pd.read_csv("results.csv")

# Plot comparison of makespans
plt.figure(figsize=(12, 6))

# Brute Force
plt.plot(df['TestCase'], df['BruteForce'], label='Brute Force (Optimal)', marker='o')
# Simulated Annealing
plt.plot(df['TestCase'], df['SimulatedAnnealing'], label='Simulated Annealing', marker='s')
# 2-Approximation
plt.plot(df['TestCase'], df['TwoApproximation'], label='2-Approximation', marker='^')

plt.title('Comparison of Scheduling Algorithms')
plt.xlabel('Test Case')
plt.ylabel('Makespan')
plt.legend()
plt.grid(True)
plt.show()
