// fn main()
// {
//     let a: i32 = 4;
//     let mut b: i32 = 5;
//     {
//         let a: bool = true;
//         let a: i32 = 6;
//         {
//             let mut b: i32 = 7;
//             b = a;
//             out b; // 6
//         }
//         out b; // 5
//     }
//     b += a;
//     out b; // 9
// }

// fn sum(a: i32, b: i32) -> i32
// {
//     return a + b;
// }

// fn main()
// {
//     let mut a: i32;
//     input a;
//     let b = &mut a;
//     if (a + 5 > 10)
//     {
//         output sum(a, a);
//     }
//     else
//     {
//         *b = 10;
//         output a;
//     }
// }

// fn myoutput(a : [i32; 4])
// {
//     for i in 0..4
//     {
//         output a[i];
//     }
// }

// fn main()
// {
//     // let mut a : (i32, [i32;4]) = (5, [1, 2, 3, 4]);
//     // output a.1[1];
//     let mut a : [i32;4] = [4, 3, 2, 1];
//     myoutput(a);
// }

// fn main()
// {
//     let mut a : bool = true;
//     if (1 > 5 || !a)
//     {
//         output 4;
//     }
//     else
//     {
//         output 3;
//     }
// }

fn matrix_mult(a: [[i32; 2]; 2], b: [[i32; 2]; 2]) -> [[i32; 2]; 2] {
    let mut result = [[0, 0], [0, 0]];
    for i in 0..2 {
        for j in 0..2 {
            for k in 0..2 {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

fn identity_matrix() -> [[i32; 2]; 2] {
    return [[1, 0], [0, 1]];
}

fn matrix_power(mut base: [[i32; 2]; 2], mut n: i32) -> [[i32; 2]; 2] {
    let mut result = identity_matrix();
    
    while n > 0 {
        if n % 2 == 1 {
            result = matrix_mult(result, base);
        }
        base = matrix_mult(base, base);
        output 111;
        n /= 2;
        output 222;
    }
    output 114514;
    return result;
}

fn fast_fibonacci(n: i32) -> i32 {
    if n == 0 {
        return 0;
    }
    
    let m = [[1, 1], [1, 0]];
    let powered = matrix_power(m, n - 1);
    output 456;
    return powered[0][0];
}

fn main() {
    identity_matrix();
    let fib = fast_fibonacci(3);
    output 123;
    output fib;
}