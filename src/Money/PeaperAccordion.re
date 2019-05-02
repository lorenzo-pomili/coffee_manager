open React;

let accordionStyle = ReactDOMRe.Style.make(~float="right", ());
let peaperStyle = ReactDOMRe.Style.make(~marginTop="10px", ());

[@react.component]
let make = (~peaperList, ~onAdd) => {
  <Accordion
    accordionStyle
    buttonLabelOpen={js|\u25B2|js}
    buttonLabelClose={js|\u25BC|js}>
    {Belt.List.mapWithIndex(peaperList, (i, c) =>
       <div key={"coins" ++ string_of_int(i)} style=peaperStyle>
         <MoneyRender onClick={m => onAdd(m)} money={Money.Peaper(c)} />
       </div>
     )
     |> Array.of_list
     |> array}
  </Accordion>;
};
