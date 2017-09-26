


var svg = d3.select("svg"),
    width = +svg.attr("width"),
    height = +svg.attr("height");

  // Define the div for the tooltip
var div = d3.select("body").append("div")
    .attr("class", "tooltip")
    .style("opacity", 0);


  // svg.append("text")
  //   .attr("x", 100)
  //   .attr("y", -70)
  //   .attr("dy", "3.5em" )
  //   .attr("text-anchor", "start")
  //   .style("font-size", "28px")
  // 	.style("font-weight", "bold")
  //   .text("SFFD Call Incidents in December 2016 ")

var pack = d3.pack()
    .size([width-100, height])
    .padding(1.5);

d3.csv("elia/bubble/bubble.csv", function(d) {
  d.value = +d["Count"];
  d.Call_Type = d["Call_Type"]

 	return d;
}, function(error, data) {
  if (error) throw error;


  var color = d3.scaleOrdinal()
  .domain(data.map(function(d){ return d.Call_Type;}))
  .range(['#fbb4ae','#b3cde3','#ccebc5','#decbe4','#fed9a6',
  '#ffe9a8','#b9bfe3','#fddaec','#cccccc']);

  var root = d3.hierarchy({children: data})
      .sum(function(d) { return d.value; })

  var node = svg.selectAll(".node")
    .data(pack(root).leaves())
    .enter().append("g")
      .attr("class", "node")
      .attr("transform", function(d) { return "translate(" + d.x + "," + d.y + ")"; });

  node.append("circle")
      .attr("id", function(d) { return d.id; })
      .attr("r", function(d) { return d.r; })
      .style("fill", function(d) { return color(d.data.Call_Type); })
      .on("mouseover", function(d) {
    div.transition()
      .duration(200)
      .style("opacity", .9);
    div	.html(d.data.Call_Type + ": <br>"+d.data.value  )
      .style("left", (d3.event.pageX) + "px")
      .style("top", (d3.event.pageY - 28) + "px");
  })
    .on("mouseout", function(d) {
    div.transition()
      .duration(500)
      .style("opacity", 0);
  });



   node.append("text")
      .text(function(d) {
     if (d.data.value > 748|| d.data.Call_Type == "Other" || d.data.Call_Type == "Fire"){
       return d.data.Call_Type;
     }
     return "";});



  var legend = svg.selectAll(".legend")
  .data(data).enter()
  .append("g")
  .attr("class","legend")
  .attr("transform", "translate(" + 780 + "," + 120+ ")");


   legend.append("rect")
     .attr("x", 0)
     .attr("y", function(d, i) { return 20 * i; })
     .attr("width", 15)
     .attr("height", 15)
		.style("fill", function(d) { return color(d.Call_Type)});


    legend.append("text")
     .attr("x", 25)
    	.attr("text-anchor", "start")
     .attr("dy", "1em")
     .attr("y", function(d, i) { return 20 * i; })
     .text(function(d) {return d.Call_Type;})
    .attr("font-size", "12px");


    legend.append("text")
     .attr("x",31)
     .attr("dy", "-.2em")
     .attr("y",-10)
     .text("Call Type")
  	.attr("font-size", "17px");


    svg.append("g")
    .attr("class", "title")
  .append("text")             // text label for the x axis
  .attr("x",0)
  .attr("y",  550 )
  .style("text-anchor", "start")
  .style("font-size", "10px")
  .text("Source: SF Opendata");

    svg.append("g")
    .attr("class", "title")
  .append("text")             // text label for the x axis
  .attr("x",0)
  .attr("y",  550 )
  .attr("dy", "1em")
  .style("text-anchor", "start")
  .style("font-size", "10px")
  .text("https://data.sfgov.org/Public-Safety/Fire-Department-Calls-for-Service-December-2016/97i8-upbq?category=Public-Safety&view_name=Fire-Department-Calls-for-Service-December-2016");

});
