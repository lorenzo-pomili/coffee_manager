open React;

let coinStyle = ReactDOMRe.Style.make(~marginLeft="10px", ());

[@react.component]
let make = (~coinList, ~onAdd) => {
  <Accordion buttonLabelOpen={js|\u25C0|js} buttonLabelClose={js|\u25B6|js}>
    {Belt.List.mapWithIndex(coinList, (i, c) =>
       <span key={"coins" ++ string_of_int(i)} style=coinStyle>
         <MoneyRender onClick={m => onAdd(m)} money={Money.Coin(c)} />
       </span>
     )
     |> Array.of_list
     |> array}
  </Accordion>;
};
