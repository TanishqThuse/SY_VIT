const svg = d3.select("svg");
const width = window.innerWidth;
const height = window.innerHeight;
svg.attr("width", width).attr("height", height);

const audioContext = new (window.AudioContext || window.webkitAudioContext)();
const analyser = audioContext.createAnalyser();
analyser.fftSize = 256;
const bufferLength = analyser.frequencyBinCount;
const dataArray = new Uint8Array(bufferLength);

const barsGroup = svg.append("g");

// Function to load audio from the microphone
function loadMicrophone() {
    navigator.mediaDevices.getUserMedia({ audio: true })
        .then(function(stream) {
            const source = audioContext.createMediaStreamSource(stream);
            source.connect(analyser);
            render(); // Start visualizing
        })
        .catch(function(err) {
            console.error('Error accessing microphone:', err);
        });
}

function createBars() {
    const bars = barsGroup.selectAll("rect")
        .data(dataArray)
        .enter()
        .append("rect")
        .attr("x", (d, i) => i * (width / bufferLength))
        .attr("width", width / bufferLength - 1)
        .attr("fill", "steelblue");
    
    return bars;
}

function drawVisualizer(bars) {
    analyser.getByteFrequencyData(dataArray);
    
    bars.attr("y", (d, i) => height - dataArray[i])
        .attr("height", (d, i) => dataArray[i]);
}

function render() {
    drawVisualizer(barsGroup.selectAll("rect"));
    requestAnimationFrame(render);
}

// Initialize microphone and start visualization
loadMicrophone();
const bars = createBars();
