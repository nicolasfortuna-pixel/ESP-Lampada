import { database } from "./firebaseConfig.js";

import {
    ref,
    set
} from "https://www.gstatic.com/firebasejs/11.10.0/firebase-database.js";


const botaoLiga = document.getElementById("botaoliga");
const botaoDesliga = document.getElementById("botaodesliga");

const lampadaRef = ref(database, "lampada/estado");


botaoLiga.addEventListener("click", function () {

    // Manda TRUE para o Firebase
    set(lampadaRef, true);

    // Parte visual
    botaoLiga.classList.add("ligado");
    botaoDesliga.classList.remove("ligado");

    document.body.classList.add("luz");

});


botaoDesliga.addEventListener("click", function () {

    // Manda FALSE para o Firebase
    set(lampadaRef, false);

    // Parte visual
    botaoDesliga.classList.add("ligado");
    botaoLiga.classList.remove("ligado");

    document.body.classList.remove("luz");

});