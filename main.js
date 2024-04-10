
function encontrarNumeroNaoRepetido(numeros) {
  const numerosJaVistos = {};
  let numeroNaoRepetido;

  for (let i = 0; i < numeros.length; i++) {
    const numeroAtual = numeros[i];

    if (!numerosJaVistos.hasOwnProperty(numeroAtual)) {
      numerosJaVistos[numeroAtual] = true;
      numeroNaoRepetido = numeroAtual;
    }
  }

  return numeroNaoRepetido;
}

const numeros = [1, 2, 3, 1, 2, 4];
const numeroNaoRepetido = encontrarNumeroNaoRepetido(numeros);

console.log(`Número não repetido: ${numeroNaoRepetido}`); // Saída: 4
