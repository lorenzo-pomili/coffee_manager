open Money;

[@react.component]
let make = (~money, ~onClick) =>
  switch (money) {
  | Coin(c) => <Coin coin=c onClick />
  | Peaper(p) => <Peaper peaper=p onClick />
  };
