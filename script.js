/* script.js */
function toggleDevice(device, state) {
    fetch(`https://your-firebase-url.firebaseio.com/home/${device}.json`, {
            method: 'PUT',
            body: JSON.stringify(state.toUpperCase()),
            headers: {
                'Content-Type': 'application/json'
            }
        })
        .then(response => response.json())
        .then(data => {
            document.getElementById("status").innerText = `${device.charAt(0).toUpperCase() + device.slice(1)} turned ${state}`;
        })
        .catch(error => console.error("Error:", error));
}

function toggleLightOn() {
    toggleDevice('light', 'on');
}

function toggleLightOff() {
    toggleDevice('light', 'off');
}

function toggleFanOn() {
    toggleDevice('fan', 'on');
}

function toggleFanOff() {
    toggleDevice('fan', 'off');
}