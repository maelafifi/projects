var script1 = document.createElement("script"),
    script2 = document.createElement("script"),
    oldD3;

function noConflict() {
    console.log(d3);
    oldD3 = d3;
    console.log("loaded old");
    // script2.type = 'text/javascript';
    script2.src = "http://d3js.org/d3.v3.min.js";
    script2.addEventListener("load", ready, false);
    document.head.appendChild(script2);
    console.log("ah",script2);
}

function ready() {
    console.log("loaded new");
    console.log(d3, oldD3);
    // document.getElementById("version1").textContent = oldD3.version;
    document.getElementById("version2").appendChild(script2);
    // document.getElementById("version1").appendChild(script1);
    // document.getElementById("version2").textContent = d3.version;
}

// script1.type = 'text/javascript';
script1.src = "http://d3js.org/d3.v4.min.js";
script1.addEventListener("load", noConflict, false);
document.head.appendChild(script1);
console.log(script1)
