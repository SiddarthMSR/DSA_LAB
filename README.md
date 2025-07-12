# DSA_LAB 📚

A comprehensive collection of **Data Structures and Algorithms** implementations developed for our DSA Lab course. This repository contains solutions to classic NP-hard problems using various algorithmic approaches including approximation algorithms, simulated annealing, and exact solutions.

---

## 🚀 Projects Overview

### 1. **Vertex Cover Problem** 🔗
**Location**: `VertexCover/` and `vertex_cover_problem.cpp`

Implementation of multiple approaches to solve the Vertex Cover problem:
- **Brute-Force** : Exact solution for small instances
- **Greedy Approximation**: 2-approximation algorithm
- **Simulated Annealing**: Metaheuristic optimization approach

**Features**:
- Multiple algorithm variants for comparison
- Interactive approach selection
- Visual output of vertex covers

### 2. **Set Cover Problem** 📦
**Location**: `SetCover/`

Comprehensive solution to the Set Cover problem with three different approaches:
- **Brute Force**: Exact solution for small instances
- **Greedy Approximation**: ln(n)-approximation algorithm
- **Simulated Annealing**: Probabilistic optimization

**Features**:
- Flexible input system (manual/hardcoded)
- Performance comparison between algorithms
- Visual assets for better understanding

### 3. **Travelling Salesman Problem (TSP)** 🗺️
**Location**: `Travelling Salesman Problem/`

Classic TSP implementation with:
- C implementation of TSP algorithm
- Jupyter notebook for visualization (`tsp_visualization.ipynb`)
- Results analysis and performance metrics

### 4. **Subset Sum Problem** 🔢
**Location**: `Subset_Sum/` and individual files

Multiple implementations:
- **Approximate Subset Sum**: FPTAS (Fully Polynomial-Time Approximation Scheme)
- **Simulated Annealing variant**: `Subset_Sum._with_SA.cpp`
- Standard dynamic programming approach

### 5. **Parallel Machine Scheduling** ⚙️
**Location**: `Parallel Machine Scheduling/` and `Simulated Annealing On Parallel Machine/`

Load balancing optimization with:
- **Greedy Algorithm**: Simple machine assignment
- **Simulated Annealing**: Advanced optimization for better load distribution

---

## 🛠️ Technologies Used

- **Languages**: C++, C, Python
- **Algorithms**: 
  - Approximation Algorithms
  - Simulated Annealing
  - Dynamic Programming
  - Greedy Algorithms
  - Binary Search
  - Bit Manipulation
- **Visualization**: Python (matplotlib), Jupyter Notebooks
- **Data Structures**: Graphs, Sets, Arrays, Vectors

---

## 📁 Repository Structure

```
DSA_LAB/
├── VertexCover/                    # Vertex Cover implementations
│   ├── main.cpp                    # Main implementation
│   ├── vertex_cover_problem.cpp    # Multiple approaches
│   └── Assets/                     # Visual demonstrations
├── SetCover/                       # Set Cover problem solutions
│   ├── main.cpp                    # Complete implementation
│   └── ReadMe.md                   # Detailed documentation
├── Travelling Salesman Problem/    # TSP solutions
│   ├── tsp.c                       # C implementation
│   ├── tsp_visualization.ipynb     # Jupyter visualization
│   └── results.txt                 # Performance results
├── Subset_Sum/                     # Subset Sum variations
│   ├── Subset_Sum.cpp              # Standard implementation
│   └── Subset_Sum._with_SA.cpp     # Simulated Annealing variant
├── Parallel Machine Scheduling/    # Scheduling algorithms
│   └── Parallel_Machine_Scheduling.cpp
├── Simulated Annealing On Parallel Machine/  # SA optimizations
│   ├── Simulated_Annealing_On_Parallel_Machine.cpp
│   └── Simulated_Annealing_On_Vertex_Cover_Problem.cpp
├── visualize.py                    # General visualization tools
├── visualize_machine.py            # Machine scheduling visualization
├── results.csv                     # Experiment results
└── *.png                          # Visualization outputs
```

---

## 🎯 Key Features

### **Algorithm Diversity**
- **Exact Algorithms**: For optimal solutions on small instances
- **Approximation Algorithms**: Polynomial-time solutions with guaranteed performance ratios
- **Metaheuristics**: Simulated Annealing for near-optimal solutions

### **Performance Analysis**
- Comparative studies between different approaches
- Runtime and quality metrics
- Visual performance representations

### **Educational Focus**
- Well-documented code with clear explanations
- Multiple implementation strategies for learning
- Step-by-step algorithm demonstrations

---

## 🚀 Getting Started

### Prerequisites
```bash
# C++ Compiler (g++)
sudo apt-get install g++

# Python (for visualizations)
sudo apt-get install python3 python3-pip

# Required Python packages
pip3 install matplotlib numpy jupyter
```

### Compilation & Execution

#### For C++ programs:
```bash
# Vertex Cover
cd VertexCover/
g++ -o main main.cpp
./main

# Set Cover
cd SetCover/
g++ -o main main.cpp
./main

# Subset Sum
g++ -o subset_sum Subset_Sum.cpp
./subset_sum
```

#### For Python visualizations:
```bash
python3 visualize.py
python3 visualize_machine.py
```

#### For Jupyter notebooks:
```bash
cd "Travelling Salesman Problem/"
jupyter notebook tsp_visualization.ipynb
```

---

## 📊 Problem Complexities

| Problem | Class | Best Known Approximation | Our Implementation |
|---------|--------|-------------------------|-------------------|
| Vertex Cover | NP-Complete | 2-approximation | ✅ Greedy, Exact, SA |
| Set Cover | NP-Hard | ln(n)-approximation | ✅ Greedy, Brute Force, SA |
| TSP | NP-Hard | 3/2-approximation (metric) | ✅ Heuristic |
| Subset Sum | NP-Complete | FPTAS | ✅ Approximate, SA |
| Machine Scheduling | NP-Hard | 4/3-approximation | ✅ Greedy, SA |

---

## 👥 Contributors

Developed by our DSA Lab team as part of the Data Structures and Algorithms course.

---

## 📝 License

This project is developed for educational purposes as part of university coursework.

---

## 🔗 References

- *Introduction to Algorithms* by Cormen, Leiserson, Rivest, and Stein
- *Approximation Algorithms* by Vijay V. Vazirani
- *Optimization by Simulated Annealing* by Kirkpatrick et al.
