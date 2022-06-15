using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace aspdotnet_react.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class WeatherForecastController : ControllerBase
    {
        private static readonly string[] Summaries = new[]
        {
            "Freezing", "Bracing", "Chilly", "Cool", "Mild", "Warm", "Balmy", "Hot", "Sweltering", "Scorching"
        };

        private readonly ILogger<WeatherForecastController> _logger;

        public WeatherForecastController(ILogger<WeatherForecastController> logger)
        {
            _logger = logger;
        }

        [HttpGet]
        public IEnumerable<WeatherForecast> Get()
        {
            var rng = new Random();
            return Enumerable.Range(1, 5).Select(index => new WeatherForecast
            {
                Date = DateTime.Now.AddDays(index),
                TemperatureC = rng.Next(-20, 55),
                Summary = Summaries[rng.Next(Summaries.Length)]
            })
            .ToArray();
        }
    }
}

/*
 * 1. Oracle DataBase에 tb_todo_item 테이블 생성
 *  1.1 필드 ( id int
 *            title nvarchar2(200)
 *            completed char(1))
 * 2. models 생성
 *      TodoItem 클래스 생성
 *      TodoItemRepository 클래스 생성
 *          목록
 *          변경(toggle)
 *          삭제(Delete)
 *          등록(Insert)
 *      TodoItemController 클래스 생성
 *          목록
 *          변경(toggle)
 *          삭제(Delete)
 *          등록(Insert)
 *      postman으로 위 함수 테스트
 * 3. 6/13에 작성한 react todo list 컴포넌트를 변경 -> asp.net core project에 포팅
 * 4. 비동기 통신을 이용해서 서버와 연동하는 기능 구현
 */      