open React;

let podStyle =
  ReactDOMRe.Style.make(
    ~borderRadius="50%",
    ~cursor="pointer",
    ~width="75px",
    ~height="75px",
    ~lineHeight="75px",
    ~fontSize="14px",
    ~textAlign="center",
    ~display="inline-block",
    ~backgroundColor="#696559",
    ~border="7px solid #EBECE4",
    (),
  );

[@react.component]
let make = (~onClick) => {
  <div onClick style=podStyle> {"Coffee" |> string} </div>;
};
