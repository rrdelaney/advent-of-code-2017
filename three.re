type action =
  | Up
  | Down
  | Left
  | Right
  | Done;

let rec mk_steps = (steps, action) =>
  switch steps {
  | 0 => []
  | _ => [action, ...mk_steps(steps - 1, action)]
  };

type position = {
  x: int,
  y: int,
  value: int,
  inc: int
};

let is_odd_square = (num) =>
  (num == 1 || num mod 2 == 1) && mod_float(sqrt(float_of_int(num)), 1.) == 0.;

let sqrt_int = (num) => num |> float_of_int |> sqrt |> int_of_float;

let rec spiral_out = (~position, ~action_queue=[], ~increment, value) => {
  let next_action_queue =
    if (position.value >= value) {
      [Done]
    } else if (is_odd_square(position.inc)) {
      let side_len = sqrt_int(position.inc);
      List.concat([
        action_queue,
        [Right],
        mk_steps(side_len, Up),
        mk_steps(side_len + 1, Left),
        mk_steps(side_len + 1, Down),
        mk_steps(side_len + 1, Right)
      ])
    } else {
      action_queue
    };
  let action = List.hd(next_action_queue);
  let next_action_queue = List.tl(next_action_queue);
  let next_position =
    switch action {
    | Done => position
    | Up => {...position, y: position.y + 1}
    | Down => {...position, y: position.y - 1}
    | Left => {...position, x: position.x - 1}
    | Right => {...position, x: position.x + 1}
    };
  if (action == Done) {
    position
  } else {
    spiral_out(
      ~position={
        ...next_position,
        inc: next_position.inc + 1,
        value: increment(next_position)
      },
      ~action_queue=next_action_queue,
      ~increment,
      value
    )
  }
};

let manhattan_distance = (value) => {
  let initial_position = {x: 0, y: 0, value: 1, inc: 1};
  let increment = (position) => position.value + 1;
  let value_position =
    spiral_out(~position=initial_position, ~increment, value);
  abs(value_position.x) + abs(value_position.y)
};

let manhattan_distance2 = (value) => {
  let initial_position = {x: 0, y: 0, value: 1, inc: 1};
  let past_values = ref([((0, 0), 1)]);
  let increment = (position) => {
    let {x, y} = position;
    let get_value = ((nx, ny)) =>
      try (List.assoc((nx, ny), past_values^)) {
      | Not_found => 0
      };
    let surrounding_points = [
      (x + 1, y),
      (x + 1, y + 1),
      (x, y + 1),
      (x - 1, y + 1),
      (x - 1, y),
      (x - 1, y - 1),
      (x, y - 1),
      (x + 1, y - 1)
    ];
    let next_value =
      List.fold_left(
        (value, point) => value + get_value(point),
        0,
        surrounding_points
      );
    past_values := [((x, y), next_value), ...past_values^];
    next_value
  };
  let value_position =
    spiral_out(~position=initial_position, ~increment, value);
  value_position.value
};
