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

// let peaperList = [Eur5, Eur10, Eur20, Eur50, Eur100, Eur200, Eur500];
let peaperList = [];

type state = {
  currentValue: float,
  moneyToAdd: list(Money.t),
  valueToAdd: float,
};

type action =
  | ChangeImportToAdd(float)
  | AddMoney(Money.t)
  | RemoveMoney(int)
  | Add;

[@react.component]
let make = (~value) => {
  let (state, dispatcher) =
    useReducer(
      (state, action) =>
        switch (action) {
        | ChangeImportToAdd(v) => {...state, valueToAdd: v}
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
            moneyToAdd: [],
            currentValue: state.currentValue +. state.valueToAdd,
            valueToAdd: 0.,
          }
        },
      {currentValue: value, valueToAdd: 0., moneyToAdd: []},
    );
  <div>
    {Belt.List.mapWithIndex(coinList, (i, c) =>
       <MoneyRender
         key={"coins" ++ string_of_int(i)}
         onClick={m => dispatcher(AddMoney(m))}
         money={Money.Coin(c)}
       />
     )
     |> Array.of_list
     |> array}
    {Belt.List.mapWithIndex(peaperList, (i, p) =>
       <MoneyRender
         key={"peapers_" ++ string_of_int(i)}
         onClick={m => dispatcher(AddMoney(m))}
         money={Money.Peaper(p)}
       />
     )
     |> Array.of_list
     |> array}
    <div>
      {"You are adding " |> string}
      {state.valueToAdd->Js.Float.toFixedWithPrecision(~digits=2) |> string}
      {{js|€|js} |> string}
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
    <AmmountToAdd
      moneyList={state.moneyToAdd}
      onClick={i => dispatcher(RemoveMoney(i))}
    />
  </div>;
};
