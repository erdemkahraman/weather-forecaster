 // Your web app's Firebase configuration
 var firebaseConfig = {
  apiKey: "AIzaSyACqn2z4p-s5WzhR_maJICp2VOy_FLdJ9E",
  authDomain: "project--db.firebaseapp.com",
  databaseURL:"https://project--db-default-rtdb.europe-west1.firebasedatabase.app",
  projectId: "project--db",
  storageBucket: "project--db.appspot.com",
  messagingSenderId: "574576997334",
  appId: "1:574576997334:web:13b08d089d9a8047b86a77"
};
  // Initialize Firebase
  firebase.initializeApp(firebaseConfig);

function updateLocation() {
  

 var fbRef_t = firebase.database().ref('datas').child('latitude');
 fbRef_t.on('value', function(snap){ 
   var latt= snap.val();
   localStorage.setItem('ltt',latt);
 });
 var fbRef_t = firebase.database().ref('datas').child('longtitude');
 fbRef_t.on('value', function(snap){ 
   var longg= snap.val();
   localStorage.setItem('lngg',longg);
 });


// Note: This example requires that you consent to location sharing when
// prompted by your browser. If you see the error "The Geolocation service
// failed.", it means you probably did not give permission for the browser to
// locate you.
let map, infoWindow;

function initMap() {
  var my_lat = Number(localStorage.getItem('ltt'));
  var my_lng = Number(localStorage.getItem('lngg'));
  
  map = new google.maps.Map(document.getElementById("map"), {
    center: { lat: my_lat, lng: my_lng},
    zoom: 17,
  });
  new google.maps.Marker({
    position: { lat: my_lat, lng: my_lng },
    title: "#",
   // icon: "https://img.icons8.com/officel/40/000000/map-pin.png",
    map: map,
  });
}

window.initMap = initMap;
}

updateLocation();
setInterval(function() {updateLocation()},10000);