// const myHeading = document.querySelector("h1");
// myHeading.textContent = "Hello world!"


// // document.querySelector("html").addEventListener("click",
// // function () {
// //     alert("别戳我,我怕疼!");
// // }
// // )


// document.querySelector("html").addEventListener("click", () => {
//     alert("别戳我,我怕疼! ");
// });

const myImage = document.querySelector("img");

myImage.onlock = () => {
    const mySrc = myImage.getAttribute("src");
    if (mySrc === "image/firefox-icon.png") {
        myImage.setAttribute("src",images/firefox2.png);
    } else {
        myImage.setAttribute("src","images/firefox-icon.webp")
    }
}
