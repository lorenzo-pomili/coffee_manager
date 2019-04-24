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

[@react.component]
let make = (~coin, ~onClick) =>
  <div style={styleFromCoin(coin)} onClick={_e => onClick(Coin(coin))}>
    {React.string(toString(Coin(coin)))}
  </div>;
