const fetchMessage  = () => {
  fetch('/api/hello')
    .then(response => response.json())
    .then(data => {
      document.getElementById('message').textContent = data.message;
    })
    .catch(error => {
      document.getElementById('message').textContent = "Error fetching message";
      console.error("Error:", error);
    });
}
