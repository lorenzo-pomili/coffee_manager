open React;
open Utils;
open Money;

let coinList = [
  Cents1,
  Cents2,
  Cents5,
  Cents10,
  Cents20,
  Cents50,
  Eur1,
  Eur2,
];

let peaperList = [Eur5, Eur10, Eur20, Eur50, Eur100, Eur200, Eur500];

type state = {
  currentValue: float,
  moneyToAdd: list(Money.t),
  valueToAdd: float,
  valueToRemove: float,
};

type action =
  | ChangeImportToAdd(float)
  | AddMoney(Money.t)
  | RemoveValue(float)
  | RemoveMoney(int)
  | Add
  | Remove;

[@react.component]
let make = (~value) => {
  let (state, dispatcher) =
    useReducer(
      (state, action) =>
        switch (action) {
        | ChangeImportToAdd(v) => {...state, valueToAdd: v}
        | RemoveValue(v) => {
            ...state,
            valueToRemove: state.valueToRemove +. v,
          }
        | AddMoney(m) =>
          let newMoneyToAdd = [m, ...state.moneyToAdd];
          {
            ...state,
            moneyToAdd: newMoneyToAdd,
            valueToAdd: valueOfList(newMoneyToAdd),
          };
        | RemoveMoney(index) =>
          let newMoneyToAdd =
            Belt.List.keepWithIndex(state.moneyToAdd, (_m, i) => i !== index);
          {
            ...state,
            moneyToAdd: newMoneyToAdd,
            valueToAdd: valueOfList(newMoneyToAdd),
          };
        | Add => {
            ...state,
            moneyToAdd: [],
            currentValue: state.currentValue +. state.valueToAdd,
            valueToAdd: 0.,
          }
        | Remove => {
            ...state,
            currentValue: state.currentValue -. state.valueToRemove,
            valueToRemove: 0.,
          }
        },
      {
        currentValue: value,
        valueToAdd: 0.,
        valueToRemove: 0.,
        moneyToAdd: [],
      },
    );
  <div>
    <PeaperAccordion peaperList onAdd={m => dispatcher(AddMoney(m))} />
    <CoinAccordion coinList onAdd={m => dispatcher(AddMoney(m))} />
    <div>
      {"You are adding " |> string}
      {state.valueToAdd->Js.Float.toFixedWithPrecision(~digits=2) |> string}
      {{js|€|js} |> string}
    </div>
    <div>
      {"You are consuming " |> string}
      {state.valueToRemove->Js.Float.toFixedWithPrecision(~digits=2) |> string}
      {{js|€|js} |> string}
      <button
        style={ReactDOMRe.Style.make(~marginLeft="10px", ())}
        onClick={_e => dispatcher(Remove)}>
        {"Consume" |> string}
      </button>
    </div>
    <div>
      {"You have " |> string}
      {state.currentValue->Js.Float.toFixedWithPrecision(~digits=2) |> string}
      {{js|€|js} |> string}
    </div>
    <div>
      <input
        onChange={e =>
          dispatcher(ChangeImportToAdd(e |> valueOfEvent |> float_of_string))
        }
      />
      <button onClick={_ => dispatcher(Add)}>
        {"Add Credit" |> string}
      </button>
    </div>
    <div
      style={ReactDOMRe.Style.make(
        ~marginTop="10px",
        ~marginBottom="10px",
        (),
      )}>
      <Pod onClick={_ => dispatcher(RemoveValue(0.5))} />
    </div>
    <AmmountToAdd
      moneyList={state.moneyToAdd}
      onConfirm={() => dispatcher(Add)}
      onClick={i => dispatcher(RemoveMoney(i))}
    />
  </div>;
};
