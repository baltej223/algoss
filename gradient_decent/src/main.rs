use std::process::exit;

#[allow(dead_code)]
fn fn_(x: f64, y: f64) -> f64 {
    0.1 * x * x + 0.07 * y * y
}

fn dr_fn_wrt_X(x: f64) -> f64 {
    0.2 * x
}

fn dr_fn_wrt_Y(y: f64) -> f64 {
    0.14 * y
}

fn Gradient_fn(x: f64, y: f64) -> (f64, f64) {
    (dr_fn_wrt_X(x), dr_fn_wrt_Y(y))
}

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
    //
    // pub fn angle_between(v1: &Vector, v2: &Vector) -> f64 {
    //     Vector::dot_product(v1, v2) / (Vector::vector_mod(v1) * Vector::vector_mod(v2))
    // }
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
    // pub fn walk(&mut self, towards: &Vector) {
    //     let new_vector = Vector::add(&self, &towards);
    // }
    pub fn print(&self) {
        let x = self.X;
        let y = self.Y;
        println!("X : {x}, Y : {y}");
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
    const LEARNING_RATE: f64 = 0.001;
    let random = Vector::new(21.0, -21.0);

    println!("Random:");
    random.print();

    let mut current = Vector::new(random.X, random.Y);
    println!("Current Vector:");
    current.print();

    // let prev_vector: Vector = random;
    loop {
        let direction_of_increase = gradient_to_vector(Gradient_fn(current.X, current.Y));
        println!("direction_of_increase");
        direction_of_increase.print();

        let mut gradient = direction_of_increase.reverse_new();
        gradient.multiply(LEARNING_RATE);
        println!("decent_direction");
        gradient.print();

        current = Vector::add(&current, &gradient);
        println!("New current");
        current.print();

        if Vector::vector_mod(&direction_of_increase) < 0.0001 {
            break;
        }

        println!("---------- next loop ----------");
    }
    print!("Found Minima");
}
