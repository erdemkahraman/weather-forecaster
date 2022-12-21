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

  function set_data(data_name, data_id){
      var data_id_V = document.getElementById(data_id);
      var fbRef_temp = firebase.database().ref('datas').child(data_name);
      fbRef_temp.on('value', snap => data_id_V.innerText = snap.val());
  }

/*var tempV = document.getElementById('temp');
var fbRef_Temp = firebase.database().ref().child('datas/Temperature');
fbRef_Temp.on('value', snap => tempV.innerText = snap.val());*/
set_data('temperature', 'temp');
set_data('pressure', 'pres');
set_data('altitude', 'alt');
set_data('air quality', 'air');
set_data('rainfall', 'rain');
set_data('humidity', 'hum');
set_data('light', 'lt');
set_data('longtitude', 'lng');
set_data('latitude', 'lat');
  

var fbRef_t = firebase.database().ref('datas').child('w-cond');
fbRef_t.on('value', function(snap){ 
  var w_cond= snap.val();
  
  if(w_cond==97) { // cold weather
    document.getElementById("w-cond").src ="C:\\Users\\dirac\\Desktop\\html_son\\resim\\cold.svg";
  }else if(w_cond==98) { // snowy weather
    document.getElementById("w-cond").src = "C:\\Users\\dirac\\Desktop\\html_son\\resim\\snow.svg";
  }else if(w_cond==99) { // warm weather
    document.getElementById("w-cond").src = "C:\\Users\\dirac\\Desktop\\html_son\\resim\\warm.svg";
  }else if(w_cond==100) { // hot weather
    document.getElementById("w-cond").src = "C:\\Users\\dirac\\Desktop\\html_son\\resim\\hot.svg";
  }else if(w_cond==101){ // rainy weather
    document.getElementById("w-cond").src = "C:\\Users\\dirac\\Desktop\\html_son\\resim\\rain.svg";
  }else{ // loading
    document.getElementById("w-cond").src = "C:\\Users\\dirac\\Desktop\\html_son\\resim\\snow.svg";
  }
});

  