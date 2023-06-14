var editor = ace.edit("editor");
editor.setTheme("ace/theme/textmate");
editor.getSession().setMode("ace/mode/c_cpp");

var simulatorFrame = document.querySelector('#viewer iframe');
var compilationFailed = document.querySelector('#compilation-failed');

if (document.location.hash) {
    if (document.location.hash.indexOf('#user') === 0) {
        var script = document.location.hash.substr(1);
        var x = new XMLHttpRequest();
        x.onload = function() {
            if (x.status === 200) {
                editor.setValue(x.responseText);
                editor.selection.clearSelection();
                editor.selection.moveCursorTo(0, 0);

                simulatorFrame.src = '/view/' + script;
                simulatorFrame.style.display = 'block';
                compilationFailed.style.display = 'none';
            }
        };
        x.open('GET', '/outUser/' + script + '.cpp');
        x.send();
    }
    else {
        var demo = document.location.hash.substr(1);
        var ix = [].map.call(document.querySelector('#select-project').options, function(p) {
            return p.getAttribute('name');
        }).indexOf(demo);

        if (ix > -1) {
            load_example(demo);
            document.querySelector('#select-project').selectedIndex = ix;
        }
    }
}

function load_example(demo) {
    var x = new XMLHttpRequest();
    x.onload = function() {
        if (x.status === 200) {
            sessionStorage.removeItem('model-dirty');

            simulatorFrame.src = '/view/' + demo;
            simulatorFrame.style.display = 'block';
            compilationFailed.style.display = 'none';

            editor.setValue(x.responseText);
            editor.selection.clearSelection();
            editor.selection.moveCursorTo(0, 0);

            document.location.hash = '#' + demo;
        }
        else {
            alert('Fallo la compilación, observe la consola...');
            console.error('Fallo cargar el ejemplo...', x.status);
        }

        if (ga && typeof ga === 'function') {
            ga('send', {
                hitType: 'event',
                eventCategory: 'load-example',
                eventAction: demo
            });
        }
    };
    x.open('GET', '/examples/' + demo + '/main.cpp');
    x.send();
}

document.querySelector('#load-example').onclick = function() {
    var sp = document.querySelector('#select-project');
    var demo = sp.options[sp.selectedIndex].getAttribute('name');
    load_example(demo);
};

document.querySelector('#load-new').onclick = function() {
    var example = 'new';
    const selectElement = document.querySelector('#select-project');
    const optionName = 'new';
    const optionIndex = Array.from(selectElement.options).findIndex(option => option.getAttribute('name') === optionName);
    selectElement.selectedIndex = optionIndex;
    load_example(example);
};

document.querySelector('#run').onclick = function() {
    var btn = this;
    btn.disabled = 'disabled';

    var status = document.querySelector('#run-status');
    status.textContent = 'Compilando...';

    var x = new XMLHttpRequest();
    x.onload = function() {
        btn.removeAttribute('disabled');

        if (x.status === 200) {
            simulatorFrame.src = '/view/' + x.responseText;
            status.textContent = '';
            document.location.hash = '#' + x.responseText;

            simulatorFrame.style.display = 'block';
            compilationFailed.style.display = 'none';
        }
        else {
            console.error('Fallo la compilación', x.status);
            console.error(x.responseText);

            status.textContent = 'Fallo la compilación';

            compilationFailed.querySelector('pre').textContent = x.responseText;
            compilationFailed.style.display = 'block';

            simulatorFrame.style.display = 'none';
        }

        if (ga && typeof ga === 'function') {
            ga('send', {
                hitType: 'event',
                eventCategory: 'compile',
                eventAction: x.status === 200 ? 'success' : 'failure'
            });
        }
    };
    x.open('POST', '/compile');
    x.setRequestHeader('Content-Type', 'application/json');
    x.send(JSON.stringify({ code: editor.getValue() }));
}


document.querySelector('#run-download').onclick = function() {
        var code = " ";
        var collection = document.getElementsByClassName("ace_line"); 

        Array.prototype.forEach.call(collection, function(el) {
            code  =  code + el.textContent + "\n";  
        });

        var e = document.querySelector('#download_code_internal');

        var sp = document.querySelector('#select-project');
        var name = sp.options[sp.selectedIndex].getAttribute('name');

        e.setAttribute("href", "data:application/octet-stream," + encodeURIComponent(code));
        e.setAttribute("download", name + ".c");
        e.click();

};

