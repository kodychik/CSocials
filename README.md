# Social Media Graph Representation in C

## Overview

This project simulates a basic social media network using graph data structures, where users are represented as nodes, and connections (friendships or follows) are represented as edges. The project implements two fundamental graph traversal algorithms:

- **BFS (Breadth-First Search)**: Used to explore the shortest path between users and to discover connections within a specific distance.
- **DFS (Depth-First Search)**: Used to explore deeper connections and detect communities or strongly connected components.

## Features

- **Graph Representation**: Users are nodes in a graph, and connections between them are edges.
- **BFS Implementation**: Find the shortest path between two users or explore all connections within a certain level of separation.
- **DFS Implementation**: Explore deep connections, detect cycles, or find strongly connected components.
- **User Management**: Add and remove users, and create or delete connections between users.
- **Connection Analysis**: Analyze the network to find the most connected users, isolated users, and more.


## Getting Started

### Prerequisites

- A C compiler (e.g., GCC)
- Make (optional, for using the Makefile)

### Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/social-media-graph.git
   cd social-media-graph
