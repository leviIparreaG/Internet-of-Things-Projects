let potLastValue = 0;
let potControlActive = false;
let potTimeout;

function setSliderState(disabled) {
    const sliders = [document.getElementById("led4"), document.getElementById("led5")];
    sliders.forEach(slider => {
        slider.disabled = disabled;
        slider.style.opacity = disabled ? '0.5' : '1';
    });
}

document.addEventListener('DOMContentLoaded', function () {
    const led1Button = document.getElementById("led1");
    const led2Button = document.getElementById("led2");
    const led3Button = document.getElementById("led3");

    const led4Slider = document.getElementById("led4");
    const led5Slider = document.getElementById("led5");

    const potentiometerValue = document.getElementById("potenciometro");
    const lightSensorValue = document.getElementById("fotoresistencia");

    // Botones LED 1-3
    led1Button.addEventListener("click", () => fetch('/led/1'));
    led2Button.addEventListener("click", () => fetch('/led/2'));
    led3Button.addEventListener("click", () => fetch('/led/3'));

    // Sliders LED 4 y 5
    led4Slider.addEventListener("input", function () {
        if (!potControlActive) {
            fetch(`/led/4/brightness/${this.value}`);
        }
    });

    led5Slider.addEventListener("input", function () {
        if (!potControlActive) {
            fetch(`/led/5/brightness/${this.value}`);
        }
    });

    // Sensores cada 1 segundo
    setInterval(function () {
        fetch('/sensor/potenciometro')
            .then(response => response.text())
            .then(data => {
                potentiometerValue.textContent = data;
                let currentVal = parseInt(data);

                if (Math.abs(currentVal - potLastValue) > 20) {
                    potControlActive = true;
                    setSliderState(true);  // Desactivar sliders
                    clearTimeout(potTimeout);
                    potTimeout = setTimeout(() => {
                        potControlActive = false;
                        setSliderState(false); // Reactivar sliders
                    }, 2000);
                }
                potLastValue = currentVal;
            });

        fetch('/sensor/fotoresistencia')
            .then(response => response.text())
            .then(data => lightSensorValue.textContent = data);
    }, 1000);
});