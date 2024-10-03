d3.json('data/sample-data.json').then(data => {
    renderDashboard(data);
});

// // const apiKey = 'YOUR_API_KEY';  // Replace with your actual OpenWeatherMap API key
// const apiKey = '5372247f726c46fb81e141932240310';
// const city = 'London';          // You can change this to any city

// const url = `https://api.openweathermap.org/data/2.5/forecast?q=${city}&appid=${apiKey}&units=metric`;

// fetch(url)
//     .then(response => response.json())
//     .then(data => {
//         const weatherData = data.list.map(item => ({
//             date: item.dt_txt.split(' ')[0],
//             temperature: item.main.temp,
//             humidity: item.main.humidity,
//             precipitation: item.rain ? item.rain['3h'] : 0
//         }));
//         renderDashboard(weatherData);
//     })
//     .catch(error => console.error('Error fetching weather data:', error));

//for static website ==> no api

const weatherData = [
{ date: '2023-09-01', temperature: 22, humidity: 60, precipitation: 5 },
{ date: '2023-09-02', temperature: 24, humidity: 55, precipitation: 0 },
{ date: '2023-09-03', temperature: 20, humidity: 70, precipitation: 10 },
{ date: '2023-09-04', temperature: 23, humidity: 65, precipitation: 2 },
{ date: '2023-09-05', temperature: 25, humidity: 50, precipitation: 0 },
];

// Call the render function with the static data
renderDashboard(weatherData);


function renderDashboard(weatherData) {
    const svg = d3.select("svg");
    const margin = { top: 20, right: 30, bottom: 30, left: 40 };
    const width = +svg.attr("width") - margin.left - margin.right;
    const height = +svg.attr("height") - margin.top - margin.bottom;

    const x = d3.scaleBand()
        .domain(weatherData.map(d => d.date))
        .range([0, width])
        .padding(0.1);

    const yTemp = d3.scaleLinear()
        .domain([0, d3.max(weatherData, d => d.temperature)])
        .range([height, 0]);

    const yHumidity = d3.scaleLinear()
        .domain([0, d3.max(weatherData, d => d.humidity)])
        .range([height, 0]);

    const g = svg.append("g")
        .attr("transform", `translate(${margin.left},${margin.top})`);

    // Draw Temperature Bars
    g.selectAll(".temp-bar")
        .data(weatherData)
        .enter()
        .append("rect")
        .attr("class", "temp-bar")
        .attr("x", d => x(d.date))
        .attr("y", d => yTemp(d.temperature))
        .attr("width", x.bandwidth())
        .attr("height", d => height - yTemp(d.temperature))
        .attr("fill", "orange");

    // Draw Humidity Bars
    g.selectAll(".humidity-bar")
        .data(weatherData)
        .enter()
        .append("rect")
        .attr("class", "humidity-bar")
        .attr("x", d => x(d.date) + x.bandwidth() / 2)
        .attr("y", d => yHumidity(d.humidity))
        .attr("width", x.bandwidth() / 2)
        .attr("height", d => height - yHumidity(d.humidity))
        .attr("fill", "blue");

    // Add Tooltip
    const tooltip = d3.select(".tooltip");

    g.selectAll(".temp-bar, .humidity-bar")
        .on("mouseover", function(event, d) {
            tooltip.style("display", "block")
                .html(`Date: ${d.date}<br>Temperature: ${d.temperature}°C<br>Humidity: ${d.humidity}%<br>Precipitation: ${d.precipitation}mm`)
                .style("left", (event.pageX + 5) + "px")
                .style("top", (event.pageY - 28) + "px");
        })
        .on("mouseout", () => {
            tooltip.style("display", "none");
        });
}
