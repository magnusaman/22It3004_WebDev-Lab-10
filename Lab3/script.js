const itemsList = document.getElementById("items-list");
const addItemForm = document.getElementById("add-item-form");

addItemForm.addEventListener("submit", function(event) {
  event.preventDefault();
  const newItemName = document.getElementById("new-item").value;
  
  const listItem = document.createElement("li");
  listItem.classList.add("list-item");
  
  const checkbox = document.createElement("input");
  checkbox.type = "checkbox";
  listItem.appendChild(checkbox);
  
  const itemText = document.createTextNode(newItemName);
  listItem.appendChild(itemText);
  
  itemsList.appendChild(listItem);
  
  document.getElementById("new-item").value = "";
});

itemsList.addEventListener("change", function(event) {
  if (event.target.type === "checkbox") {
    event.target.parentElement.classList.toggle("completed");
  }
});
