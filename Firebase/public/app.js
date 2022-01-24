// Import the functions you need from the SDKs you need
import { initializeApp } from "https://www.gstatic.com/firebasejs/9.6.2/firebase-app.js";
// import { getAuth, createUserWithEmailAndPassword, signInWithEmailAndPassword } from "https://www.gstatic.com/firebasejs/9.6.2/firebase-auth.js";
import { getDatabase , ref, set  } from "https://www.gstatic.com/firebasejs/9.6.2/firebase-database";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries



const firebaseConfig = {
  apiKey: "AIzaSyApN_UInVP2mV0jKbsdAeRPUCXDYPZuCwU",
  authDomain: "iot-aeroponics.firebaseapp.com",
  databaseURL: "https://iot-aeroponics-default-rtdb.asia-southeast1.firebasedatabase.app",
  projectId: "iot-aeroponics",
  storageBucket: "iot-aeroponics.appspot.com",
  messagingSenderId: "685018331718",
  appId: "1:685018331718:web:cdb49e6a4d29a2f2372847",
  measurementId: "G-WCYJ0TPNEX"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const auth = getAuth(app);
const database = getDatabase();

// document.getElementById("signin").addEventListener('click', function(){
//     const email = document.getElementById("email").value;
//     const password = document.getElementById("pwd").value;

//     signInWithEmailAndPassword(auth, email, password)
//     .then((userCredential) => {
//         // Signed in 
//         const user = userCredential.user;
//         // ...
//         console.log("log in");
//         location.href = "dashboard.html";
//     })
//     .catch((error) => {
//         const errorCode = error.code;
//         const errorMessage = error.message;
//         // ..
//         console.log(errorCode + errorMessage);
//     });  
// })

function writeUserData(userId, name, email, imageUrl) {
  const db = getDatabase();
  set(ref(db, 'users/' + userId), {
    username: name,
    email: email,
    profile_picture : imageUrl
  });
}