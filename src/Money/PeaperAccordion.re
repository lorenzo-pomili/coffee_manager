open React;

let getAccordionStyle = isOpen =>
  ReactDOMRe.Style.make(
    ~display={
      isOpen ? "inline-block" : "none";
    },
    (),
  );

let accordionStyle = ReactDOMRe.Style.make(~float="right", ());

let buttonStyle = ReactDOMRe.Style.make(~cursor="pointer", ());

let peaperStyle = ReactDOMRe.Style.make(~marginTop="10px", ());

type state = {isOpen: bool};

type action =
  | Toggle;

[@react.component]
let make = (~peaperList, ~onAdd) => {
  let (state, dispatcher) =
    useReducer(
      (state, action) =>
        switch (action) {
        | Toggle => {isOpen: !state.isOpen}
        },
      {isOpen: false},
    );
  <div style=accordionStyle>
    <div>
      <button style=buttonStyle onClick={_e => dispatcher(Toggle)}>
        {(state.isOpen ? {js|\u25B2|js} : {js|\u25BC|js}) |> string}
      </button>
    </div>
    <div style={getAccordionStyle(state.isOpen)}>
      {Belt.List.mapWithIndex(peaperList, (i, c) =>
         <div key={"coins" ++ string_of_int(i)} style=peaperStyle>
           <MoneyRender onClick={m => onAdd(m)} money={Money.Peaper(c)} />
         </div>
       )
       |> Array.of_list
       |> array}
    </div>
  </div>;
};
