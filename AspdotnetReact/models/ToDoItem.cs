using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace aspdotnet_react.models
{
    public class TodoItem
    {
        public int id { get; set; }
        public string title { get; set; }
        public char completed { get; set; }
    }
}
