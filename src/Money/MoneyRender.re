open Money;

let baseCoinStyle = ReactDOMRe.Style.make(~borderRadius="50%", ());

let getCoinStyle = (~dim, ~bgColor) =>
  ReactDOMRe.Style.make(
    ~cursor="pointer",
    ~width=dim,
    ~height=dim,
    ~lineHeight=dim,
    ~fontSize="14px",
    ~textAlign="center",
    ~display="inline-block",
    ~backgroundColor=bgColor,
    (),
  );

let styleFromCoin = coin => {
  let coinStyle =
    switch (coin) {
    | Cents1 => getCoinStyle(~dim="55px", ~bgColor="#F6E4D2")
    | Cents2 => getCoinStyle(~dim="60px", ~bgColor="#F6E4D2")
    | Cents5 => getCoinStyle(~dim="70px", ~bgColor="#F6E4D2")
    | Cents10 => getCoinStyle(~dim="70px", ~bgColor="#F8EDBF")
    | Cents20 => getCoinStyle(~dim="75px", ~bgColor="#F8EDBF")
    | Cents50 => getCoinStyle(~dim="85px", ~bgColor="#F8EDBF")
    | Eur1 =>
      ReactDOMRe.Style.combine(
        ReactDOMRe.Style.make(~border="7px solid #CFB784", ()),
        getCoinStyle(~dim="78px", ~bgColor="#EAEBEA"),
      )
    | Eur2 =>
      ReactDOMRe.Style.combine(
        ReactDOMRe.Style.make(~border="8px solid #EAEBEA", ()),
        getCoinStyle(~dim="82px", ~bgColor="#CFB784"),
      )
    };
  ReactDOMRe.Style.combine(baseCoinStyle, coinStyle);
};

module Coin = {
  [@react.component]
  let make = (~coin, ~onClick) =>
    <div style={styleFromCoin(coin)} onClick={_e => onClick(Coin(coin))}>
      {React.string(toString(Coin(coin)))}
    </div>;
};

let getPeaperStyle = (~dim, ~bgColor) => {
  let width = (dim *. 2.5 |> int_of_float |> string_of_int) ++ "px";
  let height = (dim |> int_of_float |> string_of_int) ++ "px";
  ReactDOMRe.Style.make(
    ~cursor="pointer",
    ~textAlign="center",
    ~backgroundColor=bgColor,
    ~width,
    ~height,
    ~lineHeight=height,
    ~color="white",
    ~margin="20px auto",
    ~display="inline-block",
    ~position="relative",
    (),
  );
};

let styleFromPeaper = peaper => {
  let peaperStyle =
    switch (peaper) {
    | Eur5 => getPeaperStyle(~dim=90., ~bgColor="#8DB5BD")
    | Eur10 => getPeaperStyle(~dim=100., ~bgColor="#E3A8A8")
    | Eur20 => getPeaperStyle(~dim=110., ~bgColor="#92C1D1")
    | Eur50 => getPeaperStyle(~dim=120., ~bgColor="#D7B379")
    | Eur100 => getPeaperStyle(~dim=130., ~bgColor="#85BB81")
    | Eur200 => getPeaperStyle(~dim=140., ~bgColor="#F6E161")
    | Eur500 => getPeaperStyle(~dim=150., ~bgColor="#D0A6BE")
    };
  peaperStyle;
};

module Peaper = {
  [@react.component]
  let make = (~peaper, ~onClick) =>
    <div
      style={styleFromPeaper(peaper)}
      onClick={_e => onClick(Peaper(peaper))}>
      {React.string(toString(Peaper(peaper)))}
    </div>;
};

[@react.component]
let make = (~money, ~onClick) =>
  switch (money) {
  | Coin(c) => <Coin coin=c onClick />
  | Peaper(p) => <Peaper peaper=p onClick />
  };
