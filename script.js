// Prevent default form submission and provide feedback
document.getElementById('contactForm').addEventListener('submit', function(event) {
    event.preventDefault(); // Prevent default form submission
    document.getElementById('formResponse').textContent = 'Namaste! Thank you for your message!';
});

// Function to open a PDF in a new tab
function openPDF() {
    window.open('bookchaptfinal.pdf');
}

// Add event listener to the "View Bookchapter" button
document.getElementById('openPdfBtn').addEventListener('click', openPDF);

// Initialize navOpen as false to track the side navigation state
var navOpen = false;

// Function to toggle the side navigation
function toggleNav() {
    navOpen = !navOpen; // Toggle the nav state
    if (navOpen) {
        document.getElementById("mySidenav").style.width = "250px"; // Open side nav
        document.getElementById("main").style.marginLeft = "250px";
    } else {
        document.getElementById("mySidenav").style.width = "0"; 
        document.getElementById("main").style.marginLeft= "0"; // Close side nav
    }
}

// Attach toggleNav function to the navToggle button click event
document.addEventListener("DOMContentLoaded", function() {
    document.getElementById("navToggle").addEventListener('click', toggleNav);
});


document.addEventListener("DOMContentLoaded", function() {
    const river = document.querySelector('.image-river');
    const images = river.querySelectorAll('img');
    river.style.animation = `slide 30s linear infinite`;
  
    // Duplicate images for a continuous loop
    images.forEach(img => {
      const clone = img.cloneNode();
      river.appendChild(clone);
    });
  });

  
  