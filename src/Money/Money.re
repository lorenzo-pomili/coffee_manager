type coin =
  | Cents1
  | Cents2
  | Cents5
  | Cents10
  | Cents20
  | Cents50
  | Eur1
  | Eur2;

type peaper =
  | Eur5
  | Eur10
  | Eur20
  | Eur50
  | Eur100
  | Eur200
  | Eur500;

type t =
  | Coin(coin)
  | Peaper(peaper);

let coinToString = coin =>
  switch (coin) {
  | Cents1 => "1 cent"
  | Cents2 => "2 cents"
  | Cents5 => "5 cents"
  | Cents10 => "10 cents"
  | Cents20 => "20 cents"
  | Cents50 => "50 cents"
  | Eur1 => "1 euro"
  | Eur2 => "2 euros"
  };

let peaperToString = peaper =>
  switch (peaper) {
  | Eur5 => "5 euros"
  | Eur10 => "10 euros"
  | Eur20 => "20 euros"
  | Eur50 => "50 euros"
  | Eur100 => "100 euros"
  | Eur200 => "200 euros"
  | Eur500 => "500 euros"
  };

let toString = money =>
  switch (money) {
  | Coin(coin) => coinToString(coin)
  | Peaper(peaper) => peaperToString(peaper)
  };

let coinToValue =
  fun
  | Cents1 => 0.01
  | Cents2 => 0.02
  | Cents5 => 0.05
  | Cents10 => 0.1
  | Cents20 => 0.2
  | Cents50 => 0.5
  | Eur1 => 1.
  | Eur2 => 2.;

let peaperToValue =
  fun
  | Eur5 => 5.
  | Eur10 => 10.
  | Eur20 => 20.
  | Eur50 => 50.
  | Eur100 => 100.
  | Eur200 => 200.
  | Eur500 => 500.;

let toValue =
  fun
  | Coin(coin) => coinToValue(coin)
  | Peaper(peaper) => peaperToValue(peaper);

let valueOfList = l =>
  Belt.List.reduce(l, 0., (acc, m) => acc +. toValue(m));
