function cambiarColorFondo() {
  const colores = ['#ffadad', '#ffd6a5', '#fdffb6', '#caffbf', '#9bf6ff', '#a0c4ff', '#bdb2ff', '#ffc6ff'];
  const colorAleatorio = colores[Math.floor(Math.random() * colores.length)];
  document.body.style.backgroundColor = colorAleatorio;
}

function mostrarInfo(opcion) {
  const infoDiv = document.getElementById('info-ser');
  let contenido = '';
  let imagenes = [];
  let descripcion = '';
  let nombre = '';

  if (opcion === 'novia') {
    imagenes = ['majito1.jpeg', 'majito2.jpeg', 'majito3.jpeg'];
    descripcion = 'Ella es Majito, ademas de ser doctora ​👩‍⚕️​, le encanta pintar ​🎨​, hornear y cocinar postres, tocar el ukelele, escribit poesia, tambien es mi novia y mi acompañante de aventuras  ❣️​​';
    nombre = 'Majito';
  } else if (opcion === 'perrito') {
    imagenes = ['pelos1.jpeg', 'pelos2.jpeg', 'pelos3.jpeg'];
    descripcion = 'Aunque se encuentre en Veracruz, es mi mejor amiga desde los 14 años, siempre estuvo en mis noches de desvelo. Le encanta enterrar calcetines y le encanta abrir pistaches para comerse solo lo de adentro 🐾​';
    nombre = 'Peloss';
  }

  contenido = `
    <div class="presentacion">
      <div class="carrusel">
        ${imagenes.map((src, i) => `
          <img class="slide" src="${src}" alt="${nombre} ${i+1}" style="display: ${i === 0 ? 'block' : 'none'};">
        `).join('')}
        <button class="prev" onclick="cambiarSlide(-1)">&#10094;</button>
        <button class="next" onclick="cambiarSlide(1)">&#10095;</button>
      </div>
      <div class="descripcion">
        <h2>${nombre}</h2>
        <p>${descripcion}</p>
      </div>
    </div>
  `;

  infoDiv.innerHTML = contenido;
  infoDiv.style.display = 'block';
  currentSlide = 0;
}

let currentSlide = 0;

function cambiarSlide(n) {
  const slides = document.querySelectorAll(".slide");
  if (slides.length === 0) return;
  slides[currentSlide].style.display = "none";
  currentSlide = (currentSlide + n + slides.length) % slides.length;
  slides[currentSlide].style.display = "block";
}
