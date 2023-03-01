

const axios = require("axios");

axios.post("http://localhost:8000").then((res) => {

console.log(res);
}).catch((err) => {
	console.log("errror");
});
