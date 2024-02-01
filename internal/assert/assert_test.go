// This code was derived from open source, see https://github.com/connectrpc/connect-go

// Copyright 2021-2024 The Connect Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package assert_test

import (
	"errors"
	"fmt"
	"testing"

	a "github.com/parandor/samples/internal/assert"
)

func TestAssertions(t *testing.T) {
	t.Parallel()

	t.Run("equal", func(t *testing.T) {
		t.Parallel()
		a.Equal(t, 1, 1, a.Sprintf("1 == %d", 1))
		a.NotEqual(t, 1, 2)
	})

	t.Run("nil", func(t *testing.T) {
		t.Parallel()
		a.Nil(t, nil)
		a.Nil(t, (*chan int)(nil))
		a.Nil(t, (*func())(nil))
		a.Nil(t, (*map[int]int)(nil))
		a.Nil(t, (*pair)(nil))
		a.Nil(t, (*[]int)(nil))

		a.NotNil(t, make(chan int))
		a.NotNil(t, func() {})
		a.NotNil(t, any(1))
		a.NotNil(t, make(map[int]int))
		a.NotNil(t, &pair{})
		a.NotNil(t, make([]int, 0))

		a.NotNil(t, "foo")
		a.NotNil(t, 0)
		a.NotNil(t, false)
		a.NotNil(t, pair{})
	})

	t.Run("zero", func(t *testing.T) {
		t.Parallel()
		var n *int
		a.Zero(t, n)
		var p pair
		a.Zero(t, p)
		var null *pair
		a.Zero(t, null)
		var s []int
		a.Zero(t, s)
		var m map[string]string
		a.Zero(t, m)
		a.NotZero(t, 3)
	})

	t.Run("error chain", func(t *testing.T) {
		t.Parallel()
		want := errors.New("base error")
		a.ErrorIs(t, fmt.Errorf("context: %w", want), want)
	})

	t.Run("unexported fields", func(t *testing.T) {
		t.Parallel()
		// Two pairs differ only in an unexported field.
		p1 := pair{1, 2}
		p2 := pair{1, 3}
		a.NotEqual(t, p1, p2)
	})

	t.Run("regexp", func(t *testing.T) {
		t.Parallel()
		a.Match(t, "foobar", `^foo`)
	})

	t.Run("panics", func(t *testing.T) {
		t.Parallel()
		a.Panics(t, func() { panic("testing") }) //nolint:forbidigo
	})
}

type pair struct {
	First, Second int
}
