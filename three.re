let rec closest_square = (~base=1, num) =>
  if (base * base >= num) {
    base
  } else {
    closest_square(~base=base + 2, num)
  };

type position = {
  size: int,
  x: int,
  y: int,
  value: int
};

let show_position = ({size, x, y, value}) =>
  print_endline(
    "("
    ++ string_of_int(x)
    ++ ", "
    ++ string_of_int(y)
    ++ ") ==> "
    ++ string_of_int(value)
  );

let rec wind_down = (position, want) => {
  let {value, size, x, y} = position;
  if (size == 1) {
    {value: 1, size: 1, x: 0, y: 0}
  } else if (value == want) {
    position
  } else {
    /* show_position(position); */
    let next_position =
      switch (x, y) {
      | (x, y) when x == size - 1 && y == size - 1 => raise(Not_found)
      | (x, y) when x == size - 1 => {...position, y: y + 1}
      | (x, 0) => {...position, x: x + 1}
      | (0, y) => {...position, y: y - 1}
      | (x, y) when y == size - 1 => {...position, x: x - 1}
      | _ => raise(Not_found)
      };
    wind_down({...next_position, value: value - 1}, want)
  }
};

let steps_from_position = ({size, x, y}) => {
  let mid = (size - 1) / 2;
  abs(mid - x) + abs(mid - y)
};

let manhattan_distance = (value) => {
  let size = closest_square(value);
  let inital_position = {
    x: size - 2,
    y: size - 1,
    value: size * size - 1,
    size
  };
  let value_position = wind_down(inital_position, value);
  steps_from_position(value_position)
};
