
var labels = true; // show the text labels beside individual boxplots?

var margin = {top: 10, right: 50, bottom: 145, left: 70};
var  width = 960 - margin.left - margin.right;
var height = 600 - margin.top - margin.bottom;

var min = Infinity,
    max = -Infinity;

// parse in the data
d3.csv("elia/boxplot/boxplot.csv", function(error, csv) {

	// using an array of arrays with
	// data[n][2]
	// where n = number of columns in the csv file
	// data[i][0] = name of the ith column
	// data[i][1] = array of values of ith column

	var data = [];
	data[0] = [];
	data[1] = [];
	data[2] = [];
	data[3] = [];
  data[4] = [];
  data[5] = [];
  data[6] = [];
  data[7] = [];

	// add more rows if your csv file has more columns

	// add here the header of the csv file
	data[0][0] = "Alarms";
	data[1][0] = "Fire";
	data[2][0] = "Hazard";
	data[3][0] = "Citzen_Assist";
  data[4][0] = "Rescue";
  data[5][0] = "Vehicle_Related";
  data[6][0] = "Other";
  data[7][0] = "Medical_Incident";
	// add more rows if your csv file has more columns

	data[0][1] = [];
	data[1][1] = [];
	data[2][1] = [];
	data[3][1] = [];
  data[4][1] = [];
  data[5][1] = [];
  data[6][1] = [];
  data[7][1] = [];

	csv.forEach(function(x) {
		var v1 = +x.Alarms,
			v2 = +x.Fire,
			v3 = +x.Hazard,
			v4 = +x.Citizen_Assist,
      v5 = +x.Rescue,
      v6 = +x.Vehicle_Related,
      v7 = +x.Other,
      v8 = +x.Medical_Incident;

//     		var v1 = Math.floor(x.Alarms),
// 			v2 = Math.floor(x.Fire),
// 			v3 = Math.floor(x.Hazard),
// 			v4 = Math.floor(x.Citizen_Assist),
//       v5 = Math.floor(x.Rescue),
//       v6 =  Math.floor(x.Vehicle_Related),
//       v7 =  Math.floor(x.Other),
//       v8 =  Math.floor(x.Medical_Incident);
			// add more variables if your csv file has more columns

    arr = [v1,v2,v3,v4,v5,v6,v7,v8]
// 		var rowMax = Math.max(v1, Math.max(v2, Math.max(v3, Math.max(v4,Math.max(v5, Math.max(v6, Math.max(v7,v8)))))));
// 		var rowMin = Math.min(v1, Math.min(v2, Math.min(v3, Math.min(v4,Math.min(v5, Math.min(v6, Math.min(v7,v8)))))));
    var rowMax = Math.max(v1,v2,v3,v4,v5,v6,v7,v8);
    var rowMin = Math.min(v1,v2,v3,v4,v5,v6,v7,v8);

		data[0][1].push(v1);
		data[1][1].push(v2);
		data[2][1].push(v3);
		data[3][1].push(v4);
    data[4][1].push(v5);
		data[5][1].push(v6);
		data[6][1].push(v7);
		data[7][1].push(v8);

		 // add more rows if your csv file has more columns

		if (rowMax > max) max = rowMax;
		if (rowMin < min) min = rowMin;

    max = 15



	});

	var chart = d3.box()
		.whiskers(iqr(1.5))
		.height(height)
		.domain([min, max])
		.showLabels(labels);

	var svg = d3.select("#version1").append("svg")
		.attr("width", width + margin.left + margin.right)
		.attr("height", height + margin.top + margin.bottom)
		.attr("class", "box")
		.append("g")
		.attr("transform", "translate(" + margin.left + "," + margin.top + ")");

	// the x-axis
	var x = d3.scale.ordinal()
		.domain(data.map(function(d) { return d[0] } ) )
		.rangeRoundBands([0 , width], 0.7, 0.3);

	var xAxis = d3.svg.axis()
		.scale(x)
		.orient("bottom");

	// the y-axis
	var y = d3.scale.linear()
		.domain([min, max])
		.range([height + margin.top, 0 + margin.top]);

	var yAxis = d3.svg.axis()
    .scale(y)
    .orient("left")

	// draw the boxplots
	svg.selectAll(".box")
      .data(data)
	  .enter().append("g")
		.attr("transform", function(d) { return "translate(" +  x(d[0])  + "," + margin.top + ")"; } )
      .call(chart.width(x.rangeBand()));


	// // add a title
	// svg.append("text")
  //       .attr("x", (width / 2))
  //       .attr("y", -25)
  //       .attr("text-anchor", "middle")
  //       .style("font-size", "28px")
  //       .style("font-weight", "bold")
  //       .text("SFFD Average Response Times by Call Type in Dec 2016");

	 // draw y axis
	svg.append("g")
        .attr("class", "y axis")
        .call(yAxis)
		.append("text") // and text1
		  .attr("transform", "rotate(-90)")
		  .attr("y", -50)
  		.attr("x", -178)
		  .attr("dy", ".71em")
		  .style("text-anchor", "end")
		  .style("font-size", "14px")
  		.style("font-weight", "bold")
		  .text("Response Time [Minutes]");

	// draw x axis
	svg.append("g")
      .attr("class", "x axis")
      .attr("transform", "translate(0," + (height  + margin.top + 10) + ")")
      .call(xAxis)
	  .append("text")             // text label for the x axis
    .attr("x", (width / 2) )
    .attr("y",  40 )
    .attr("dy", ".71em")
    .style("text-anchor", "middle")
    .style("font-size", "14px")
    .style("font-weight", "bold")
    .text("Call Type");


    svg.append("g")
  .attr("class", "title")
.append("text")             // text label for the x axis
.attr("x",0)
.attr("y",  530 )
.style("text-anchor", "start")
.style("font-size", "10px")
.text("Source: SF Opendata");

  svg.append("g")
  .attr("class", "title")
.append("text")             // text label for the x axis
.attr("x",0)
.attr("y",  530 )
.attr("dy", "1em")
.style("text-anchor", "start")
.style("font-size", "10px")
.text("https://data.sfgov.org/Public-Safety/Fire-Department-Calls-for-Service-December-2016/97i8-upbq?category=Public-Safety&view_name=Fire-Department-Calls-for-Service-December-2016");
});

// Returns a function to compute the interquartile range.
function iqr(k) {
  return function(d, i) {
    var q1 = d.quartiles[0],
        q3 = d.quartiles[2],
        iqr = (q3 - q1) * k,
        i = -1,
        j = d.length;
    while (d[++i] < q1 - iqr);
    while (d[--j] > q3 + iqr);
    return [i, j];
  };
}
