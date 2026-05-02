use rand::RngExt;

#[allow(dead_code)]

// fn fn_(x: f64, y: f64) -> f64 {
//     0.1 * x * x + 0.07 * y * y
// }
//
// fn dr_fn_wrt_X(x: f64) -> f64 {
//     0.2 * x
// }
//
// fn dr_fn_wrt_Y(y: f64) -> f64 {
//     0.14 * y
// }
//
// fn Gradient_fn(x: f64, y: f64) -> (f64, f64) {
//     (dr_fn_wrt_X(x), dr_fn_wrt_Y(y))
// }
//

fn fn_(x: f64, y: f64) -> f64 {
    // Multi-minima landscape using sinusoidal waves + quadratic bowl
    (x.sin() * y.cos()) + 0.05 * (x * x + y * y)
}

fn dr_fn_wrt_X(x: f64, y: f64) -> f64 {
    // Partial derivative wrt x
    x.cos() * y.cos() + 0.1 * x
}

fn dr_fn_wrt_Y(x: f64, y: f64) -> f64 {
    // Partial derivative wrt y
    -x.sin() * y.sin() + 0.1 * y
}

fn Gradient_fn(x: f64, y: f64) -> (f64, f64) {
    (dr_fn_wrt_X(x, y), dr_fn_wrt_Y(x, y))
}

#[derive(Clone)]
struct Vector {
    pub X: f64,
    pub Y: f64,
}
impl Vector {
    pub fn new(x: f64, y: f64) -> Vector {
        Vector { X: x, Y: y }
    }

    pub fn reverse(&mut self) {
        self.X = -self.X;
        self.Y = -self.Y;
    }
    pub fn reverse_new(&self) -> Vector {
        Vector {
            X: -self.X,
            Y: -self.Y,
        }
    }
    // pub fn dot_product(v1: &Vector, v2: &Vector) -> f64 {
    //     v1.X * v2.X + v2.Y * v2.X
    // }
    //
    pub fn vector_mod(x: &Vector) -> f64 {
        (x.X * x.X + x.Y * x.Y).sqrt()
    }
    pub fn add(v1: &Vector, v2: &Vector) -> Vector {
        Vector {
            X: v1.X + v2.X,
            Y: v1.Y + v2.Y,
        }
    }
    pub fn difference(v1: &Vector, v2: &Vector) -> Vector {
        Vector {
            X: v1.X - v2.X,
            Y: v1.Y - v2.Y,
        }
    }
    pub fn print(&self) {
        let x = self.X;
        let y = self.Y;
        //println!("X : {x}, Y : {y}");
    }

    pub fn multiply(&mut self, n: f64) {
        self.X *= n;
        self.Y *= n;
    }
}

fn gradient_to_vector((x, y): (f64, f64)) -> Vector {
    Vector { X: x, Y: y }
}

fn main() {
    const BOUND_FROM: f64 = 0.0;
    const BOUND_TO: f64 = 100.0;
    const LEARNING_RATE: f64 = 0.01;

    let mut rng = rand::rng();

    let mut points: Vec<Vector> = vec![];

    for _ in 0..200 {
        let random: Vector = Vector::new(
            rng.random_range(BOUND_FROM..BOUND_TO),
            rng.random_range(BOUND_FROM..BOUND_TO),
        );
        points.push(random);
    }

    let mut minimas: Vec<Vector> = vec![];

    for i in 0..points.len() {
        let random = &points[i];
        //println!("Random:");
        random.print();

        let mut current = Vector::new(random.X, random.Y);
        //println!("Current Vector:");
        current.print();

        // let prev_vector: Vector = random;
        loop {
            let direction_of_increase = gradient_to_vector(Gradient_fn(current.X, current.Y));
            //println!("direction_of_increase");
            direction_of_increase.print();

            let mut gradient = direction_of_increase.reverse_new();
            gradient.multiply(LEARNING_RATE);
            //println!("decent_direction");
            gradient.print();

            current = Vector::add(&current, &gradient);
            //println!("New current");
            current.print();

            if Vector::vector_mod(&direction_of_increase) < 0.0001 {
                break;
            }

            //println!("---------- next loop ----------");
        }
        //println!("Found Minima");
        minimas.push(current);
    }

    for minima in &minimas {
        // println!("X:{} Y:{}", minima.X, minima.Y);
    }

    let mut distinct_minimas: Vec<Vector> = Vec::new();
    let threshold: f64 = 0.001;
    for minima in minimas {
        let mut is_duplicate = false;

        for existing in &distinct_minimas {
            let diff = Vector::difference(&minima, existing);

            if Vector::vector_mod(&diff) < threshold {
                is_duplicate = true;
                break;
            }
        }

        if !is_duplicate {
            distinct_minimas.push(minima);
        }
    }

    for minima in distinct_minimas {
        println!("X:{}, Y:{}", minima.X, minima.Y);
    }
}
