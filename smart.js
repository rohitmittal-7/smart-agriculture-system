function generateRandom(min, max) {
  return Math.floor(Math.random() * (max - min + 1)) + min;
}

function updateSensorData() {
  document.getElementById('moisture').textContent = generateRandom(30, 70);
  document.getElementById('temperature').textContent = generateRandom(20, 35);
}

// Simulate sensor data updates every 5 seconds
setInterval(updateSensorData, 5000);
updateSensorData();
