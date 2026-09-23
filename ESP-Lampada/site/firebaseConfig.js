import { initializeApp } from "https://www.gstatic.com/firebasejs/11.10.0/firebase-app.js";
import { getAuth } from "https://www.gstatic.com/firebasejs/11.10.0/firebase-auth.js";
import { getDatabase } from "https://www.gstatic.com/firebasejs/11.10.0/firebase-database.js";

const firebaseConfig = {
  apiKey: "AIzaSyD_sYsXnnnw82H6qUWLe25z3zoarqL03HQ",
  authDomain: "luze-7340c.firebaseapp.com",
  databaseURL: "https://luze-7340c-default-rtdb.firebaseio.com",
  projectId: "luze-7340c",
  storageBucket: "luze-7340c.firebasestorage.app",
  messagingSenderId: "66820864775",
  appId: "1:66820864775:web:0a744424e9b460a06ce3a2",
  measurementId: "G-FJV77B2PDQ"
};

const app = initializeApp(firebaseConfig);

const auth = getAuth(app);

const database = getDatabase(app);

export { auth, database };