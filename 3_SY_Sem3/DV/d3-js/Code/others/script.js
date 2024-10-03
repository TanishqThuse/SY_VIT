// Select the SVG element from the DOM
const svg = d3.select("svg");

// Get the width and height of the window for full-screen visualization
const width = window.innerWidth;
const height = window.innerHeight;

// Set the width and height of the SVG element
svg.attr("width", width).attr("height", height);

// Create the audio context and analyser node
const audioContext = new (window.AudioContext || window.webkitAudioContext)();
const analyser = audioContext.createAnalyser();
analyser.fftSize = 256; // FFT size controls the frequency resolution
const bufferLength = analyser.frequencyBinCount; // Half the fftSize
const dataArray = new Uint8Array(bufferLength); // Array to hold frequency data

// Create a group element to hold the bars
const barsGroup = svg.append("g");

// Function to load and play the audio file
function loadAudio() {
    // Replace 'audio.mp3' with the actual file path of your audio
    const audioElement = new Audio('audio.mp3');
    
    // Create a media element source from the audio element
    const source = audioContext.createMediaElementSource(audioElement);
    
    // Connect the source to the analyser and the audio context destination (speakers)
    source.connect(analyser);
    analyser.connect(audioContext.destination);
    
    // Play the audio
    audioElement.play();
    
    return audioElement;
}

// Function to create the visualizer bars using D3.js
function createBars() {
    const bars = barsGroup.selectAll("rect")
        .data(dataArray)
        .enter()
        .append("rect")
        .attr("x", (d, i) => i * (width / bufferLength)) // Position the bars horizontally
        .attr("width", width / bufferLength - 1) // Width of each bar
        .attr("fill", "steelblue"); // Set the color of the bars
    
    return bars;
}

// Function to update the bar heights based on frequency data
function drawVisualizer(bars) {
    analyser.getByteFrequencyData(dataArray); // Get the frequency data from the analyser
    
    // Update the bars' heights and positions
    bars.attr("y", (d, i) => height - dataArray[i])
        .attr("height", (d, i) => dataArray[i]); // Set the height based on frequency value
}

// Function to continuously update and animate the visualization
function render() {
    drawVisualizer(barsGroup.selectAll("rect")); // Update the bars
    requestAnimationFrame(render); // Recursively call render for smooth animation
}

// Load the audio file and start the visualizer
const audioElement = loadAudio();
const bars = createBars(); // Create the bars once
render(); // Start the render loop
