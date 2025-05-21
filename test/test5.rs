fn merge(a: &mut[i32;20],b: &mut[i32;20], l:i32, r:i32)
{
    let m = (l + r) / 2;
    let mut lp = l;
    let mut rp = m + 1;
    let mut np = l;
    while lp <= m && rp <= r
    {
        if (*a)[lp] <= (*a)[rp]
        {
            (*b)[np] = (*a)[lp];
            np += 1;
            lp += 1;
        }
        else
        {
            (*b)[np] = (*a)[rp];
            np += 1;
            rp += 1;
        }
    }
    while lp <= m
    {
        (*b)[np] = (*a)[lp];
        np += 1;
        lp += 1;
    }
    while rp <= r
    {
        (*b)[np] = (*a)[rp];
        np += 1;
        rp += 1;
    }
    for i in l..(r+1)
    {
        (*a)[i] = (*b)[i];
    }
}
fn sort(a: &mut[i32;20],b: &mut[i32;20], l:i32, r:i32)
{
    if (l < r) {
        let m = (l + r) / 2;
        sort(a, b, l, m);
        sort(a, b, m + 1, r);
        merge(a, b, l, r);
    }
}
fn main()
{
    let mut a = [8,5,-61,84,45,-62,98,45,-45,47,-95,-8,-9,-23,5,-8,6,75,-24,91];
    let mut b:[i32;20];
    sort(&mut a, &mut b, 0, 19);
    for ai in a {
        out ai;
    }
    // for i in 0..20
    // {
    //     out a[i];
    // }
}



// fn nnn(a:i32)->i32
// {
//     if a > 1
//     {
//         return a * nnn(a-1);
//     }
//     else
//     {
//         return 1;
//     }
// }
// fn main() {
//     out nnn(12);
// }


// fn s1(a:&mut [i32;4]){
//     (*a)[3] = 9;
// }
// fn s2(a:&mut [i32;4]){
//     s1(a);
// }
// fn main(){
//     let mut a = [1,2,3,4];
//     s2(&mut a);
//     out a[3];
// }


// fn main() {
//     let mut a:i32 = 12;
//     let mut sum = 1;
    
//     while a > 0
//     {
//         sum *= a;
//         a -= 1;
//     }
//     out sum;
// }

// fn main()
// {
//     let m = (0 + 19) / 2;
//     let mut lp = 0;
//     let mut rp = m + 1;
//     let mut np = 0;
//     let mut a = [1,2,6,8,13,78,90,345,789,888,-5,4,43,67,89,123,256,543,678,890];
//     let mut b:[i32;20];
//     while lp <= m && rp <= 20
//     {
//         if a[lp] <= a[rp]
//         {
//             b[np] = a[lp];
//             np += 1;
//             lp += 1;
//         }
//         else
//         {
//             b[np] = a[rp];
//             np += 1;
//             rp += 1;
//         }
//     }
//     while lp <= m
//     {
//         b[np] = a[lp];
//         np += 1;
//         lp += 1;
//     }
//     while rp <= 19
//     {
//         b[np] = a[rp];
//         np += 1;
//         rp += 1;
//     }
//     for i in 0..20
//     {
//         out b[i];
//     }
// }

// fn main()
// {
//     let mut i = 10;
//     for j in 0..(i-1)
//     {
//         out j;
//     }
// }