open React;

let getAccordionStyle = isOpen =>
  ReactDOMRe.Style.make(
    ~display={
      isOpen ? "inline-block" : "none";
    },
    (),
  );

let buttonStyle = ReactDOMRe.Style.make(~cursor="pointer", ());

let coinStyle = ReactDOMRe.Style.make(~marginLeft="10px", ());

type state = {isOpen: bool};

type action =
  | Toggle;

[@react.component]
let make = (~coinList, ~onAdd) => {
  let (state, dispatcher) =
    useReducer(
      (state, action) =>
        switch (action) {
        | Toggle => {isOpen: !state.isOpen}
        },
      {isOpen: false},
    );
  <div>
    <div>
      <button style=buttonStyle onClick={_e => dispatcher(Toggle)}>
        {(state.isOpen ? {js|\u25B6|js} : {js|\u25C0|js}) |> string}
      </button>
    </div>
    <div style={getAccordionStyle(state.isOpen)}>
      {Belt.List.mapWithIndex(coinList, (i, c) =>
         <span key={"coins" ++ string_of_int(i)} style=coinStyle>
           <MoneyRender onClick={m => onAdd(m)} money={Money.Coin(c)} />
         </span>
       )
       |> Array.of_list
       |> array}
    </div>
  </div>;
};
