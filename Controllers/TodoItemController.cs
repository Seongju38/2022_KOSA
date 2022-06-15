using aspdotnet_react.models;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace aspdotnet_react.Controllers
{
    [ApiController]
    [Route("[controller]")] // 외부에서 TodoItemController를 호출할 때 Controller를 빼고 호출 가능하게 함
    public class TodoItemController : ControllerBase
    {
        [HttpGet]
        [Route("createBulkTodos")] // 테스트 할 때 TodoItem/createBulkTodos를 치면 나오게 함
                                   // 테스트 하는 것은 브라우저 또는 postman을 사용하면 됨
        public JsonResult createBulkTodos()
        {
            TodoItemRepository todoItemRepository = new TodoItemRepository();
            todoItemRepository.createBulkTodos(); // 데이터 넣기

            return new JsonResult("{stateResult: success}");
        }
    }
}
