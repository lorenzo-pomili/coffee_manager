[@react.component]
let make = (~moneyList, ~onClick) =>
  <div>
    {Belt.List.mapWithIndex(moneyList, (i, m) =>
       <MoneyRender
         key={"moneyToAdd" ++ string_of_int(i)}
         onClick={_e => onClick(i)}
         money=m
       />
     )
     |> Array.of_list
     |> React.array}
  </div>;
