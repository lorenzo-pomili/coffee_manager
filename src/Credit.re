open Utils;
[@react.component]
let make = (~value) =>
  <div>
    {"You have " |> rs}
    {value->Js.Float.toFixedWithPrecision(~digits=2) |> rs}
    {{js|€|js} |> rs}
  </div>;
