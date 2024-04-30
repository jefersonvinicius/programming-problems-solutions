const MIN = 2 ** 31 * -1;
const MAX = 2 ** 31 - 1;

function reverse(x: number): number {
  let reversed = '';
  if (x < 0) reversed += '-';
  const withoutSign = String(Math.abs(x));
  for (let i = withoutSign.length - 1; i >= 0; i--) {
    reversed += withoutSign[i];
  }
  const reversedAsNumber = Number(reversed);
  return reversedAsNumber > MAX || reversedAsNumber < MIN ? 0 : reversedAsNumber;
}
