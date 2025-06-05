// window.onload = response;

// global variable visible to all java functions
var xmlHttp = createXmlHttpObject();
// function to create XML object
function createXmlHttpObject() {
    if (window.XMLHttpRequest) {
        xmlHttp = new XMLHttpRequest();
    }
    else {
        xmlHttp = new ActiveXObject("Microsoft.XMLHTTP");
    }
    return xmlHttp;
}
// Function to display Wi-Fi networks as a list
function displayWifiNetworks(networks) {
    const wifiList = document.getElementById('wifiList');
    wifiList.innerHTML = ''; // Clear any existing content

    networks.forEach(network => {
        const listItem = document.createElement('li');
        listItem.textContent = network.ssid; // Assuming each object has an "ssid" field
        wifiList.appendChild(listItem);
    });
}

// Function to fetch Wi-Fi networks from the server
async function fetchWifiNetworks() {
    try {
        const response = await fetch('networks.json'); // Replace with the correct endpoint
        if (!response.ok) {
            throw new Error(`HTTP error! Status: ${response.status}`);
        }

        const networks = await response.json();
        displayWifiNetworks(networks);
    } catch (error) {
        console.error('Error fetching Wi-Fi networks:', error);
        document.getElementById('wifiList').innerHTML = "<li>Error loading networks</li>";
    }
}
// document.addEventListener('DOMContentLoaded', fetchWifiNetworks);

if (window.location.href == "config.html") {
    // Fetch and display Wi-Fi networks on page load

    // document.getElementById('wifiForm').addEventListener('submit', function (event) {
    //     event.preventDefault();
    //     const ssid = document.getElementById('ssid').value;
    //     const security = document.getElementById('security').value;
    //     const networksDiv = document.getElementById('networks');

    //     const networkDiv = document.createElement('div');
    //     networkDiv.classList.add('network');
    //     networkDiv.textContent = `Network: ${ssid}, Security: ${security}`;
    //     networksDiv.appendChild(networkDiv);

    //     document.getElementById('ssid').value = ''; // Reset form fields
    //     document.getElementById('security').value = '';
    // });
}
function listAllSavedSsid() {

}

function btnConfig() {
    window.location.href = "config.html";
}

function btnHome() {
    window.location.href = "/";
}

function btnChange(id) {
    var xhttp = new XMLHttpRequest();
    xhttp.open("PUT", "BUTTON_CHANGE?VALUE=" +
        document.getElementById("txbChange_" +
            String(id)).value +
        "&ID=" + String(id), true);
    xhttp.send();
}

function btnReset() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("PUT", "BUTTON_RESET", false);
    xhttp.send();
}

function btnDelete(id) {
    var xhttp = new XMLHttpRequest();
    xhttp.open("PUT", "BUTTON_DELETE?ID=" + String(id), true);
    xhttp.send();
}

// function to handle the response from the ESP
function response() {
    var message;
    var xmlResponse;
    var xmldoc;
    var dt = new Date();

    // get the xml stream
    xmlResponse = xmlHttp.responseXML;

    // get host date and time
    document.getElementById("time").innerHTML = dt.toLocaleTimeString();
    document.getElementById("date").innerHTML = dt.toLocaleDateString();

    if (xmlResponse != null) {
        //update actual time 
        xmldoc = xmlResponse.getElementsByTagName("N999");
        message = xmldoc[0].firstChild.nodeValue;
        document.getElementById("txbChange_999").value = message;
        xmldoc = xmlResponse.getElementsByTagName("T999");
        message = xmldoc[0].firstChild.nodeValue;
        document.getElementById("lblTime_999").innerHTML = message ;
    }
}

// general processing code for the web page to ask for an XML steam
// this is actually why you need to keep sending data to the page to 
// force this call with stuff like this
// server.on("/xml", SendXML);
// otherwise the page will not request XML from the ESP, and updates will not happen
function process() {

    if (xmlHttp.readyState == 0 || xmlHttp.readyState == 4) {
        xmlHttp.open("PUT", "xml", true);
        xmlHttp.onreadystatechange = response;
        xmlHttp.send(null);
    }
    // you may have to play with this value, big pages need more porcessing time, and hence
    // a longer timeout
    setTimeout("process()", 200);
}

