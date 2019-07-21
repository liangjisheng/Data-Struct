#!/usr/bin/python3

# the graph
graph = {}
graph["start"] = {}
graph["start"]["a"] = 6
graph["start"]["b"] = 2

graph["a"] = {}
graph["a"]["fin"] = 1

graph["b"] = {}
graph["b"]["a"] = 3
graph["b"]["fin"] = 5

graph["fin"] = {}

# print(graph)

# the costs table
infinity = float("inf")
costs = {}
costs["a"] = 6
costs["b"] = 2
costs["fin"] = infinity

# the parents table
parents = {}
parents["a"] = "start"
parents["b"] = "start"
parents["fin"] = None

processed = []

def find_lowest_cost_node(costs):
    lowest_cost = float("inf")
    lowest_cost_node = None
    # Go through each node.
    # 遍历所有节点
    for node in costs:
        cost = costs[node]
        # If it's the lowest cost so far and hasn't been processed yet...
        # 如果当前节点的开销更低且未处理过
        if cost < lowest_cost and node not in processed:
            # ... set it as the new lowest-cost node.
            # 就将其视为开销最低的节点
            lowest_cost = cost
            lowest_cost_node = node
    return lowest_cost_node

# Find the lowest-cost node that you haven't processed yet.
# 在未处理的节点中找出开销最小的节点
node = find_lowest_cost_node(costs)
# If you've processed all the nodes, this while loop is done.
# 这个while循环在所有节点都被处理后结束
while node is not None:
    cost = costs[node]
    # Go through all the neighbors of this node.
    # 遍历当前节点的所有邻居
    neighbors = graph[node]
    for n in neighbors.keys():
        new_cost = cost + neighbors[n]
        # If it's cheaper to get to this neighbor by going through this node...
        # 如果经当前节点前往该邻居更近
        if costs[n] > new_cost:
            # ... update the cost for this node.
            # 更新该邻居的开销
            costs[n] = new_cost
            # This node becomes the new parent for this neighbor.
            # 同时该邻居的父节点设置为当前节点
            parents[n] = node
    # Mark the node as processed.
    # 将当前节点标记为处理过
    processed.append(node)
    # Find the next node to process, and loop.
    # 找出接下来要处理的节点，并循环
    node = find_lowest_cost_node(costs)

print("Cost from the start to each node:")
print(costs)
