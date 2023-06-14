(function() {

    var acc = document.querySelector('#collapseButton');
    var visible = !0;
   
    acc.addEventListener("click", function() {
      visible? hide() : show();
    });

    function hide() {
         acc.classList.add('editor__sidebar__collapseButton_collapsed'),
    
         document.getElementById('sidebar').animate({
                        right: "-269px"
                    },{
                       duration: 500,
                       fill: 'forwards'
                     })
         visible = !1;
    }
   
    function show() {
         acc.classList.remove("editor__sidebar__collapseButton_collapsed"),
    
         document.getElementById('sidebar').animate({
                        right: "0px"
                    },{
                       duration: 500,
                       fill: 'forwards'
                     })
         visible = !0;
    }
      
    
})();
    