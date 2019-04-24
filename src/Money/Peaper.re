open Money;

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

[@react.component]
let make = (~peaper, ~onClick) =>
  <div
    style={styleFromPeaper(peaper)} onClick={_e => onClick(Peaper(peaper))}>
    {React.string(toString(Peaper(peaper)))}
  </div>;
