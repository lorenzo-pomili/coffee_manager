open React;

let getAccordionStyle = isOpen =>
  ReactDOMRe.Style.make(
    ~display={
      isOpen ? "inline-block" : "none";
    },
    (),
  );

let baseAccordionStyle = ReactDOMRe.Style.make();

let getAccordionStyleFromProps = accordionStyle =>
  switch (accordionStyle) {
  | None => baseAccordionStyle
  | Some(s) => ReactDOMRe.Style.combine(s, baseAccordionStyle)
  };

let buttonStyle = ReactDOMRe.Style.make(~cursor="pointer", ());

type state = {isOpen: bool};

type action =
  | Toggle;

[@react.component]
let make = (~accordionStyle=?, ~buttonLabelOpen, ~buttonLabelClose, ~children) => {
  let (state, dispatcher) =
    useReducer(
      (state, action) =>
        switch (action) {
        | Toggle => {isOpen: !state.isOpen}
        },
      {isOpen: false},
    );
  <div style={getAccordionStyleFromProps(accordionStyle)}>
    <div>
      <button style=buttonStyle onClick={_e => dispatcher(Toggle)}>
        {(state.isOpen ? buttonLabelOpen : buttonLabelClose) |> string}
      </button>
    </div>
    <div style={getAccordionStyle(state.isOpen)}> children </div>
  </div>;
};
