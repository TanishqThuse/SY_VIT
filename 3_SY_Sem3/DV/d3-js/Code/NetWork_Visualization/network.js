const width = 800;
const height = 600;

// Sample data: Nodes and Links
const graph = {
    nodes: [
        { id: "A" },
        { id: "B" },
        { id: "C" },
        { id: "D" },
        { id: "E" }
    ],
    links: [
        { source: "A", target: "B" },
        { source: "A", target: "C" },
        { source: "B", target: "D" },
        { source: "C", target: "D" },
        { source: "C", target: "E" }
    ]
};

// Create SVG canvas
const svg = d3.select("svg")
    .attr("viewBox", [0, 0, width, height]);

// Create simulation
const simulation = d3.forceSimulation(graph.nodes)
    .force("link", d3.forceLink(graph.links).id(d => d.id).distance(150))
    .force("charge", d3.forceManyBody().strength(-300))
    .force("center", d3.forceCenter(width / 2, height / 2));

// Draw links (edges)
const link = svg.append("g")
    .selectAll("line")
    .data(graph.links)
    .enter()
    .append("line")
    .attr("class", "link");

// Draw nodes
const node = svg.append("g")
    .selectAll("circle")
    .data(graph.nodes)
    .enter()
    .append("circle")
    .attr("class", "node")
    .attr("r", 20)
    .call(drag(simulation));

// Add labels to nodes
const label = svg.append("g")
    .selectAll("text")
    .data(graph.nodes)
    .enter()
    .append("text")
    .text(d => d.id)
    .attr("dy", 4);

// Simulation tick function
simulation.on("tick", () => {
    link
        .attr("x1", d => d.source.x)
        .attr("y1", d => d.source.y)
        .attr("x2", d => d.target.x)
        .attr("y2", d => d.target.y);

    node
        .attr("cx", d => d.x)
        .attr("cy", d => d.y);

    label
        .attr("x", d => d.x)
        .attr("y", d => d.y);
});

// Dragging functionality for nodes
function drag(simulation) {
    function dragstarted(event, d) {
        if (!event.active) simulation.alphaTarget(0.3).restart();
        d.fx = d.x;
        d.fy = d.y;
    }

    function dragged(event, d) {
        d.fx = event.x;
        d.fy = event.y;
    }

    function dragended(event, d) {
        if (!event.active) simulation.alphaTarget(0);
        d.fx = null;
        d.fy = null;
    }

    return d3.drag()
        .on("start", dragstarted)
        .on("drag", dragged)
        .on("end", dragended);
}
